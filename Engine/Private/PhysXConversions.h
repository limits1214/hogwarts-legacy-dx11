#pragma once

#include <DirectXMath.h>
#include <foundation/PxQuat.h>

namespace Engine
{
	inline physx::PxQuat ToNormalizedPxQuat(const DirectX::XMFLOAT4& vRotation)
	{
		const physx::PxQuat tRotation{
			vRotation.x, vRotation.y, vRotation.z, vRotation.w };
		if (tRotation.magnitudeSquared() > 0.f)
			return tRotation.getNormalized();

		return physx::PxQuat{ physx::PxIdentity };
	}
}
