#include "pch.h"
#include "ComPxFixedJoint.h"
#include "ComPxCharacterController.h"
#include "ComPxRigidBody.h"

#pragma push_macro("new")
#undef new

#include "PxPhysicsAPI.h"

#pragma pop_macro("new")

using namespace physx;

NS_USING(Engine)

CComPxFixedJoint::CComPxFixedJoint()
{
}

CComPxFixedJoint::CComPxFixedJoint(
	const CComPxFixedJoint& Prototype)
	: CComPxJoint{ Prototype }
{
}

CComPxFixedJoint::~CComPxFixedJoint()
{
}

HRESULT CComPxFixedJoint::Initialize(void* pArg)
{
	const auto* pDesc = static_cast<DESC*>(pArg);
	if (!pDesc)
		return E_FAIL;

	CComPxJoint::DESC tJointDesc = *pDesc;
	if (pDesc->bPreserveCurrentPose)
		PreserveCurrentPose(tJointDesc);

	if (FAILED(CComPxJoint::Initialize(&tJointDesc)))
		return E_FAIL;

	auto* pPhysics = CGameInstance::Get().PxGetPhysics();
	if (!pPhysics)
		return E_FAIL;

	PxFixedJoint* pJoint = PxFixedJointCreate(
		*pPhysics,
		GetActorA(),
		ToPxTransform(GetLocalFrameA()),
		GetActorB(),
		ToPxTransform(GetLocalFrameB()));
	if (!pJoint)
		return E_FAIL;

	if (!AttachJoint(pJoint))
	{
		pJoint->release();
		return E_FAIL;
	}

	return S_OK;
}

UPtr<CComPxFixedJoint> CComPxFixedJoint::Create()
{
	auto pInstance = ToUPtr(new CComPxFixedJoint{});
	if (FAILED(pInstance->InitializePrototype()))
	{
		MSG_BOX("Failed to Created : CComPxFixedJoint");
		return nullptr;
	}

	return pInstance;
}

UPtr<CPrototype> CComPxFixedJoint::Clone(void* pArg)
{
	auto pInstance = ToUPtr(new CComPxFixedJoint{ *this });
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CComPxFixedJoint");
		return nullptr;
	}

	return pInstance;
}

void CComPxFixedJoint::Free()
{
	CComPxJoint::Free();
}
