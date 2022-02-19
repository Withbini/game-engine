#include "Common.hpp"
#include "Game.hpp"
#include "VertexArray.hpp"
#include "Renderer.hpp"
#include "Mesh.hpp"
#include "MeshComponent.hpp"
#include "Texture.hpp"
#include "SpriteComponent.hpp"

#include "GBuffer.hpp"
#include "Image.hpp"
#include "LightComponent.hpp"

#include "Random.hpp"
#include "Format.hpp"

Renderer::Renderer(Game* game)
	:mGame(game)
	, mViewMatrix(Matrix4::Identity)
	, mProjMatrix(Matrix4::Identity)
	, mSpriteShader(nullptr)
	, mSpriteVerts(nullptr)
{
}

Renderer::~Renderer()
{
}

bool Renderer::Initialize(float width, float height)
{
	mScreenWidth = width;
	mScreenHeight = height;

	constexpr int gl_major_version = 4;
	constexpr int gl_minor_version = 5;
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, gl_major_version);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, gl_minor_version);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	mWindow = SDL_CreateWindow("Game Programming", 100, 100, static_cast<int>(mScreenWidth), static_cast<int>(mScreenHeight), SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	mContext = SDL_GL_CreateContext(mWindow);

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		SDL_Log("Failed to initialize glad");
		return false;
	}
	auto glVersion = glGetString(GL_VERSION);
	SDL_Log("OpenGL context version: %s", glVersion);

	mImGuiContext = ImGui::CreateContext();
	ImGui::SetCurrentContext(mImGuiContext);
	if (!ImGui_ImplSDL2_InitForOpenGL(mWindow, mContext))
	{
		SDL_Log("Failed to initialize IMGUI.");
		return false;
	}
	ImGui_ImplOpenGL3_Init();
	ImGui_ImplOpenGL3_CreateFontsTexture();
	ImGui_ImplOpenGL3_CreateDeviceObjects();

	if (!LoadShaders())
	{
		SDL_Log("Failed to load shaders.");
		return false;
	}
	CreateSpriteVerts();

	mGBuffer = FrameBuffer::Create({
		Texture::Create(static_cast<int>(width), static_cast<int>(height), GL_RGBA16F, GL_FLOAT),
		Texture::Create(static_cast<int>(width), static_cast<int>(height), GL_RGBA16F, GL_FLOAT),
		Texture::Create(static_cast<int>(width), static_cast<int>(height), GL_RGBA, GL_UNSIGNED_BYTE),
		});


	mPointLightMesh = GetMesh("Assets/PointLight.gpmesh");
	mMirrorBuffer = FrameBuffer::Create({ Texture::Create(static_cast<int>(width / 4), static_cast<int>(height / 4), GL_RGB,GL_FLOAT) });

	mSsaoBuffer = FrameBuffer::Create({ Texture::Create(static_cast<int>(width), static_cast<int>(height), GL_RED) });

	//random vector √ ±‚»≠
	{
		vector<glm::vec3> ssaoNoise;
		ssaoNoise.resize(16);
		for (size_t i = 0; i < ssaoNoise.size(); ++i)
		{
			glm::vec3 sample(Random::GetFloatRange(-1., 1.), Random::GetFloatRange(-1., 1.), Random::GetFloatRange(-1., 1.));
			ssaoNoise[i] = sample;
		}
		mSsaoNoiseTexture = Texture::Create(4, 4, GL_RGB16F, GL_FLOAT);
		mSsaoNoiseTexture->Bind();
		mSsaoNoiseTexture->SetFilter(GL_NEAREST, GL_NEAREST);
		mSsaoNoiseTexture->SetWrap(GL_REPEAT, GL_REPEAT);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 4, 4, GL_RGB, GL_FLOAT, ssaoNoise.data());
	}

	//
	{
		m_ssaoSamples.resize(64);
		for (size_t i = 0; i < m_ssaoSamples.size(); i++)
		{
			glm::vec3 sample(
				Random::GetFloatRange(-1.0f, 1.0f),
				Random::GetFloatRange(-1.0f, 1.0f),
				Random::GetFloatRange(0.0f, 1.0f));
			sample = glm::normalize(sample) * Random::GetFloatRange(0.0f, 1.0f);

			// scale for slightly shift to center
			float t = (float)i / (float)m_ssaoSamples.size();
			float t2 = t * t;
			float scale = (1.0f - t2) * 0.1f + t2 * 1.0f;

			m_ssaoSamples[i] = sample * scale;
		}
	}

	{
		mBlurBuffer = FrameBuffer::Create({
			Texture::Create(static_cast<int>(width), static_cast<int>(height), GL_RED)
			});
	}

	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);
	return true;
}

void Renderer::Shutdown()
{
	ImGui_ImplOpenGL3_DestroyFontsTexture();
	ImGui_ImplOpenGL3_DestroyDeviceObjects();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext(mImGuiContext);

	delete mSpriteVerts;
	delete mSpriteShader;
	delete mMeshShader;
	delete mGGlobalShader;
	SDL_GL_DeleteContext(mContext);
	SDL_DestroyWindow(mWindow);
}

void Renderer::UnloadData()
{
	mTextures.clear();

	for (auto meshes : mMeshes)
	{
		meshes.second->UnLoad();
		delete meshes.second;
	}
	mMeshes.clear();
}

void Renderer::SetUniforms(Shader* shader, Matrix4& view) const
{
	Matrix4 invView = view;
	invView.Invert();
	shader->setVec3("ambient", mAmbient);
	shader->setVec3("cameraPos", invView.GetTranslation());
	shader->SetFloat("specPower", mSpecPower);

	shader->setVec3("dirLight.direction", mDirLight.mDirection);
	shader->setVec3("dirLight.diffuseColor", mDirLight.mDiffuseColor);
	shader->setVec3("dirLight.specColor", mDirLight.mSpecColor);
}

void Renderer::Draw()
{
	//DrawScene(mMirrorBuffer->GetFrameBufferID(), mMirrorView, mProjMatrix, 0.25f);
	DrawScene(mGBuffer->GetFrameBufferID(), mViewMatrix, mProjMatrix, 1.f);

	{
		BindBuffer(mSsaoBuffer->GetFrameBufferID());
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		SetViewport(mScreenWidth, mScreenHeight);
		mSsaoShader->Bind();
		mGBuffer->BindTextures();
		mSsaoNoiseTexture->Bind(3);
		glActiveTexture(GL_TEXTURE0);
		mSsaoShader->SetInt("gNormal", 1);
		mSsaoShader->SetInt("gPosition", 2);
		mSsaoShader->SetInt("texNoise", 3);
		mSsaoShader->SetMat4("view", mViewMatrix);
		mSsaoShader->SetMat4("proj", mProjMatrix);
		mSsaoShader->SetMat4("viewProj", mViewMatrix*mProjMatrix);
		mSsaoShader->setVec2("noiseScale", mScreenWidth / (float)mSsaoNoiseTexture->GetWidth(),
			mScreenHeight / (float)mSsaoNoiseTexture->GetHeight());
		mSsaoShader->SetFloat("radius", mSsaoRadius);
		for (auto i = 0; i < m_ssaoSamples.size(); ++i)
		{
			auto sampleName = Format::string_format("samples[%d]", i);
			mSsaoShader->setVec3(sampleName, m_ssaoSamples[i]);
		}
		for (auto *m : mMeshComps)
		{
			//m->BindTextures(mSsaoShader);
			m->Draw(mSsaoShader);
		}

		BindBuffer(mBlurBuffer->GetFrameBufferID());
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		SetViewport(mScreenWidth, mScreenHeight);
		mBlurShader->Bind();
		mSsaoBuffer->GetTexture(0)->Bind();
		mBlurShader->SetInt("tex", 0);
		mBlurShader->SetMat4("viewProj", mViewMatrix*mProjMatrix);
		for (auto *m : mMeshComps)
		{
			//m->BindTextures(mBlurShader);
			m->Draw(mBlurShader);
		}
	}
	BindBuffer(0);
	DrawFromGBuffer();

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	mSpriteShader->Bind();
	mSpriteVerts->Bind();
	for (auto comp : mSprites)
	{
		if (comp->GetVisible())
			comp->Draw(mSpriteShader);
	}

	//explicit imgui new frame
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	if (ImGui::Begin("G-Buffers"))
	{
		const char* bufferNames[] = {
			"albedo/spec", "normal", "position"
		};
		static int bufferSelect = 0;
		ImGui::Combo("buffer", &bufferSelect, bufferNames, sizeof(bufferNames) / sizeof(const char*));

		const float width = ImGui::GetContentRegionAvail().x;
		const float height = width * (mScreenHeight / mScreenWidth);
		ImGui::Image(reinterpret_cast<ImTextureID>(mGBuffer->GetTexture(bufferSelect)->GetTextureID()),
			ImVec2(width, height), ImVec2(0, 1), ImVec2(1, 0));
	}
	ImGui::End();
	if (ImGui::Begin("directional light"))
	{
		ImGui::DragFloat3("position", glm::value_ptr(mDirLight.mDirection), 0.1f, -200, 200);
		ImGui::ColorEdit3("albedo", glm::value_ptr(mDirLight.mDiffuseColor));
		ImGui::ColorEdit3("spec", glm::value_ptr(mDirLight.mSpecColor));
	}
	ImGui::End();
	if (ImGui::Begin("mirror"))
	{
		const float width = ImGui::GetContentRegionAvail().x;
		const float height = width * (mScreenHeight / mScreenWidth);
		ImGui::Image(reinterpret_cast<ImTextureID>(mMirrorBuffer->GetTexture()->GetTextureID()),
			ImVec2(width, height), ImVec2(0, 1), ImVec2(1, 0));
	}
	ImGui::End();
	if (ImGui::Begin("ssao param"))
	{
		const float width = ImGui::GetContentRegionAvail().x;
		const float height = width * (mScreenHeight / mScreenWidth);
		ImGui::DragFloat("radius", &mSsaoRadius, 0.1f, 1.f, 200.f);
		ImGui::Checkbox("Use SSAO", &useSsao);

	}
	ImGui::End();
	if (ImGui::Begin("SSAO")) {
		const float width = ImGui::GetContentRegionAvail().x;
		const float height = width * ((float)mScreenHeight / (float)mScreenWidth);

		ImGui::Image((ImTextureID)mSsaoBuffer->GetTexture()->GetTextureID(),
			ImVec2(width, height), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::Image((ImTextureID)mBlurBuffer->GetTexture()->GetTextureID(),
			ImVec2(width, height), ImVec2(0, 1), ImVec2(1, 0));
	}
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	SDL_GL_SwapWindow(mWindow);
}

void Renderer::DrawScene(unsigned framebuffer, const Matrix4& view, const Matrix4& proj, float viewportScale)
{
	BindBuffer(framebuffer);
	SetViewport(mScreenWidth*viewportScale, mScreenHeight*viewportScale);

	glClearColor(0.f, 0.f, 0.f, 1.f);
	glDepthMask(GL_TRUE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	mMeshShader->Bind();
	mMeshShader->SetMat4("viewProj", view*proj);
	SetUniforms(mMeshShader, mViewMatrix);
	for (auto comp : mMeshComps)
	{
		if (comp->GetVisible())
		{
			comp->BindTextures(mMeshShader);
			comp->Draw(mMeshShader);
		}
	}
}

void Renderer::CreateSpriteVerts()
{
	float vertices[] = {
		-0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 0.f,
		0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 0.f,
		0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 1.f,
		-0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 1.f
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	mSpriteVerts = new VertexArray(vertices, 4, indices, 6);
}

bool Renderer::LoadShaders()
{
	mSpriteShader = new Shader("src/Shader/Sprite.vert", "src/Shader/Sprite.frag");
	mSpriteShader->Bind();
	const Matrix4 viewProj = Matrix4::CreateSimpleViewProj(mScreenWidth, mScreenHeight);
	mSpriteShader->SetMat4("viewProj", viewProj);

	mMeshShader = new Shader("src/Shader/Phong.vert", "src/Shader/GBuffer.frag");
	//mMeshShader = new Shader("src/Shader/Phong.vert", "src/Shader/Phong.frag");
	mMeshShader->Bind();
	mViewMatrix = Matrix4::CreateLookAt(Vector3::Zero, Vector3::UnitX, Vector3::UnitZ);
	mProjMatrix = Matrix4::CreatePerspectiveFOV(Math::ToRadians(70.f), mScreenWidth, mScreenHeight, 10.0f, 10000.f);
	mMeshShader->SetMat4("viewProj", mViewMatrix * mProjMatrix);

	mGGlobalShader = new Shader("src/Shader/GBufferGlobal.vert", "src/Shader/GBufferGlobal.frag");
	mGGlobalShader->Bind();
	mGGlobalShader->SetInt("gAlbedoSpec", 0);
	mGGlobalShader->SetInt("gNormal", 1);
	mGGlobalShader->SetInt("gPosition", 2);
	mGGlobalShader->SetMat4("viewProj", viewProj);
	const Matrix4 gbufferWorld = Matrix4::CreateScale(mScreenWidth, -mScreenHeight, 1.f);
	mGGlobalShader->SetMat4("world", gbufferWorld);

	mGPointLightShader = new Shader("src/Shader/Phong.vert", "src/Shader/GBufferPointLight.frag");
	mGPointLightShader->Bind();
	mGPointLightShader->SetInt("gAlbedoSpec", 0);
	mGPointLightShader->SetInt("gNormal", 1);
	mGPointLightShader->SetInt("gPosition", 2);
	mGPointLightShader->SetMat4("viewProj", viewProj);
	mGPointLightShader->setVec2("screenDimensions", static_cast<float>(mScreenWidth), static_cast<float>(mScreenHeight));

	mSsaoShader = new Shader("src/Shader/SSAO.vert", "src/Shader/SSAO.frag");

	mBlurShader = new Shader("src/Shader/blur5x5.vert", "src/Shader/blur5x5.frag");
	mBlurShader->Bind();
	mBlurShader->SetMat4("world", gbufferWorld);
	return true;
}

void Renderer::DrawFromGBuffer()
{
	glDisable(GL_DEPTH_TEST);
	mGGlobalShader->Bind();
	mSpriteVerts->Bind();
	mGBuffer->BindTextures();
	//mSsaoBuffer->GetTexture(0)->Bind(3);
	mBlurBuffer->GetTexture(0)->Bind(3);
	mGGlobalShader->SetInt("ssao", 3);
	mGGlobalShader->SetInt("useSSAO", useSsao == true ? 1 : 0);
	SetUniforms(mGGlobalShader, mViewMatrix);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	//mGBuffer->ReadBuffer();
	//const int width = static_cast<int>(mScreenWidth);
	//const int height = static_cast<int>(mScreenHeight);
	//glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_DEPTH_BUFFER_BIT, GL_NEAREST); // depth buffer from g-buffer

	//glEnable(GL_DEPTH_TEST); //use depth test
	//glDepthMask(GL_FALSE); //do not write depth buffer

	//mGPointLightShader->Bind();
	//mPointLightMesh->GetVertexArray()->Bind();
	//mGPointLightShader->SetMat4("viewProj", mViewMatrix * mProjMatrix);
	//mGBuffer->BindTextures();

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_ONE, GL_ONE);
	//for (auto* light : mLightComponents)
	//{
	//	light->Draw(mGPointLightShader, mPointLightMesh);
	//}
}

TexturePtr Renderer::GetTexture(const std::string& fileName)
{
	const auto textureFromFile = mTextures.find(fileName);
	if (textureFromFile == mTextures.end())
	{
		auto image = Image::Load(fileName);
		auto texture = Texture::CreateFromImage(image.get());
		mTextures.insert({ fileName, texture });

		return mTextures.find(fileName)->second;
	}
	return textureFromFile->second;
}

Mesh* Renderer::GetMesh(const std::string& fileName)
{
	const auto meshFromFile = mMeshes.find(fileName);
	if (meshFromFile == mMeshes.end())
	{
		auto* mesh = new Mesh();
		mesh->Create(fileName, this);
		mMeshes.insert({ fileName, mesh });
		return mesh;
	}
	return meshFromFile->second;
}

void Renderer::AddSprite(SpriteComponent* sprite)
{
	const int drawOrder = sprite->GetDrawOrder();
	auto it = mSprites.begin();
	for (; it != mSprites.end(); ++it)
	{
		if (drawOrder < (*it)->GetDrawOrder())
		{
			break;
		}
	}
	mSprites.insert(it, sprite);
}

void Renderer::RemoveSprite(SpriteComponent* sprite)
{
	auto delSprite = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(delSprite);
}

void Renderer::AddMesh(MeshComponent* mesh)
{
	mMeshComps.emplace_back(mesh);
}

void Renderer::RemoveMesh(MeshComponent* mesh)
{
	auto del = std::find(mMeshComps.begin(), mMeshComps.end(), mesh);
	if (del != mMeshComps.end())
		mMeshComps.erase(del);
}

Vector3 Renderer::Unproject(const Vector3& screenPoint) const
{
	Vector3 nDC = screenPoint;
	nDC.x /= mScreenWidth * 0.5f;
	nDC.y /= mScreenHeight * 0.5f;
	Matrix4 mat = mViewMatrix * mProjMatrix;
	mat.Invert();
	return Vector3::TransformWithPerspDiv(nDC, mat);
}

void Renderer::AddPointLight(class LightComponent* light)
{
	mLightComponents.emplace_back(light);
}

void Renderer::RemovePointLight(class LightComponent* light)
{
	auto l = std::find(mLightComponents.begin(), mLightComponents.end(), light);
	if (l != mLightComponents.end())
	{
		std::iter_swap(l, mLightComponents.end() - 1);
		mLightComponents.pop_back();
	}
}