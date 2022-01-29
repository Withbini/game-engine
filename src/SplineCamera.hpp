#pragma once
#include <memory>
#include <vector>

#include "CameraComponent.hpp"

struct Spline
{
	std::vector<Vector3> mControlPoints;
	size_t getNumControlPoints() const { return mControlPoints.size(); }
	Vector3 Compute(size_t idx, float t) const
	{
		//TODO: n-order CatmullRom
		if (idx >= mControlPoints.size()) return mControlPoints.back();
		if (idx == 0) return mControlPoints[idx];
		if (idx + 2 >= mControlPoints.size()) return mControlPoints[idx];

		Vector3 p0 = mControlPoints[idx - 1];
		Vector3 p1 = mControlPoints[idx];
		Vector3 p2 = mControlPoints[idx + 1];
		Vector3 p3 = mControlPoints[idx + 2];

		//CatmullRom spline
		return 0.5f * (2 * p1 + (p2 - p0)*t + (2 * p0 - 5 * p1 + 4 * p2 - p3)*t*t + (-1 * p0 + 3 * p1 - 3 * p2 + p3)*t*t*t);
	}
};
class SplineCamera :
	public CameraComponent
{
public:
	SplineCamera(class Actor* owner);
	~SplineCamera() override = default;

	void Update(float deltaTime) override;
	void SetSpline(std::unique_ptr<Spline> path) { mPath = std::move(path); }
	void SetPause(bool b) { mPause = b; }
private:
	std::unique_ptr<Spline> mPath;
	float mT;
	size_t mIndex;
	float mSpeed;
	bool mPause;
};