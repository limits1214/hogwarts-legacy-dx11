#include "pch.h"
#include "LevelLogo.h"
#include "GameInstance.h"
#include "LevelLoading.h"
#include "Level_Defines.h"

#include "FlyCamera.h"

#include "ResCBuffer.h"
#include "BackGround.h"
#include "UiCamera.h"

#include "LevelLogoLoader.h"

// UI
#include "UIManager.h"
#include "UIController.h"
#include "VideoObject.h"
#include "TextureUI.h"
#include <chrono>
#include <iomanip>
#include <memory>
#include <sstream>
#include <vector>

NS_USING(Client)

CLevelLogo::CLevelLogo()
	: CLevel{ ETOUI(LEVEL::LOGO) }
{
}

CLevelLogo::~CLevelLogo()
{
}

HRESULT CLevelLogo::Initialize()
{
	E::CGameInstance::Get().GameObjectAllResetExceptLayers({
		"00_ENGINE_CINEMATIC_CAMERA"
	});
	//Engine::CGameInstance::Get().GameObjectLayerInitialize(E::ETOUI(LEVEL_LOADING_LAYERS::END), LevelLoadingLayersToString);

	//{
	//	CBackGround::UIOBJECT_DESC Desc{};
	//	Desc.sObjectTag = "BackGround";
	//	if (!(E::CGameInstance::Get().AddGameObjectToLayer("LEVEL_LOGO", "Prototype_GameObject_BackGround",
	//		"00_OBJECTS", &Desc)))
	//	{
	//		return E_FAIL;
	//	}
	//}


	// 여기다 테스트용 벤치마크 코드
#pragma region StringID_DerivedType_Benchmark
	{
		// [LSY] 벤치마크는 기본 비활성화. 측정할 때만 true로 변경한다.
		constexpr bool bRunBenchmark = false;
		static bool bBenchmarkCompleted = false;
		if (bRunBenchmark && !bBenchmarkCompleted)
		{
			bBenchmarkCompleted = true;
			constexpr size_t iIterations = 1'000'000;
			constexpr size_t iSampleCount = 256;
			std::vector<std::string> leftStrings;
			std::vector<std::string> rightStrings;
			std::vector<E::StringID> leftIDs;
			std::vector<E::StringID> rightIDs;
			leftStrings.reserve(iSampleCount);
			rightStrings.reserve(iSampleCount);
			leftIDs.reserve(iSampleCount);
			rightIDs.reserve(iSampleCount);
			for (size_t i = 0; i < iSampleCount; ++i)
			{
				// 같은 길이와 공통 접두사. 절반은 동일하고 절반은 마지막 문자만 다르다.
				leftStrings.push_back("Prototype_GameObject_Benchmark_Resource_" + std::to_string(i) + "_A");
				rightStrings.push_back(leftStrings.back());
				if (i % 2 != 0)
					rightStrings.back().back() = 'B';
				leftIDs.emplace_back(leftStrings.back());
				rightIDs.emplace_back(rightStrings.back());
			}

			// [LSY] 결과 저장을 유지하고 캐스팅할 포인터를 매 반복마다 읽는다.
			volatile bool bEqualResult = false;
			CLevelLogo* volatile pCastResult = nullptr;
			E::CLevel* volatile pBase = this;

			// std::string 비교
			auto start = std::chrono::steady_clock::now();
			for (size_t i = 0; i < iIterations; ++i)
			{
				const size_t index = i % iSampleCount;
				bEqualResult = leftStrings[index] == rightStrings[index];
			}
			const double stringTime = std::chrono::duration<double, std::milli>(
				std::chrono::steady_clock::now() - start).count();

			// StringID 비교
			start = std::chrono::steady_clock::now();
			for (size_t i = 0; i < iIterations; ++i)
			{
				const size_t index = i % iSampleCount;
				bEqualResult = leftIDs[index] == rightIDs[index];
			}
			const double stringIDTime = std::chrono::duration<double, std::milli>(
				std::chrono::steady_clock::now() - start).count();

			// static_cast
			start = std::chrono::steady_clock::now();
			for (size_t i = 0; i < iIterations; ++i)
			{
				pCastResult = static_cast<CLevelLogo*>(pBase);
			}
			const double staticTime = std::chrono::duration<double, std::milli>(
				std::chrono::steady_clock::now() - start).count();

			// dynamic_cast
			start = std::chrono::steady_clock::now();
			for (size_t i = 0; i < iIterations; ++i)
			{
				pCastResult = dynamic_cast<CLevelLogo*>(pBase);
			}
			const double dynamicTime = std::chrono::duration<double, std::milli>(
				std::chrono::steady_clock::now() - start).count();

			// DerivedType 기반 Engine::Cast
			start = std::chrono::steady_clock::now();
			for (size_t i = 0; i < iIterations; ++i)
			{
				pCastResult = E::Cast<CLevelLogo>(pBase);
			}
			const double derivedTime = std::chrono::duration<double, std::milli>(
				std::chrono::steady_clock::now() - start).count();

			std::wostringstream stringResult;
			stringResult << std::fixed << std::setprecision(3)
				<< L"std::string: " << stringTime << L" ms\n"
				<< L"StringID: " << stringIDTime << L" ms";
			MessageBoxW(nullptr, stringResult.str().c_str(), L"StringID 비교 - 100만 회", MB_OK);

			std::wostringstream castResult;
			castResult << std::fixed << std::setprecision(3)
				<< L"static_cast: " << staticTime << L" ms\n"
				<< L"dynamic_cast: " << dynamicTime << L" ms\n"
				<< L"Engine::Cast: " << derivedTime << L" ms";
			MessageBoxW(nullptr, castResult.str().c_str(), L"캐스팅 비교 - 100만 회", MB_OK);
		}
	}
#pragma endregion

	{
		E::CCameraObject::CAMERA_DESC Desc{};
		Desc.eProj = E::CCameraObject::PROJ::PERSPECTIVE;
		Desc.vAt = { 0.f, 0.f, 0.f };
		Desc.vEye = { 0.f, 0.f, -5.f };
		Desc.fAspect = { g_iWinSizeX / (E::_float)g_iWinSizeY };
		Desc.fFovY = 75.f;
		Desc.fNear = 0.1f;
		Desc.fFar = 100.f;
		Desc.sObjectTag = "FlyCam";

		if (auto flyCam = E::CGameInstance::Get().AddGameObjectToLayer("CAMERAS", "Prototype_GameObject_FlyCamera",
			"99_CAMERA", &Desc))
		{
			if (FAILED(E::CGameInstance::Get().RegistCamera("FLY", flyCam.value())))
			{
				int x = 0;
			}
			E::CGameInstance::Get().SetActiveCamera("FLY");
		}
	}

	{
		E::CCameraObject::CAMERA_DESC Desc{};
		Desc.eProj = E::CCameraObject::PROJ::ORTHOGRAPHIC;
		Desc.fNear = 0.f;
		Desc.fFar = 1.f;
		Desc.fWidth = g_iWinSizeX;
		Desc.fHeight = g_iWinSizeY;
		Desc.sObjectTag = "UICam";
		Desc.vEye = { 0.f, 0.f, -0.1f };

		if (auto uiCam = E::CGameInstance::Get().AddGameObjectToLayer("CAMERAS", "Prototype_GameObject_UICamera",
			"99_CAMERA", &Desc))
		{
			if (FAILED(E::CGameInstance::Get().RegistCamera("UI", uiCam.value())))
			{
				int x = 0;
			}

#pragma region SharedPtr_Handle_Benchmark
			{
				// [LSY] 참조 방식 벤치마크는 측정할 때만 true로 변경한다.
				constexpr bool bRunReferenceBenchmark = false;
				static bool bReferenceBenchmarkCompleted = false;
				if (bRunReferenceBenchmark && !bReferenceBenchmarkCompleted)
				{
					bReferenceBenchmarkCompleted = true;
					constexpr size_t iIterations = 1'000'000;
					auto& game = E::CGameInstance::Get();
					const CHandle handle = uiCam.value();
					E::CGameObject* pObject = game.GetGameObjectByHandle(handle);
					// [LSY] 객체의 실제 소유권은 매니저에 유지한다. 테스트용 control block만 생성한다.
					// 빈 삭제자로 이중 해제를 방지하며 복사 시 shared_ptr의 참조 카운트는 정상 동작한다.
					const std::shared_ptr<E::CGameObject> sharedObject(pObject, [](E::CGameObject*) {});
					E::CGameObject* volatile pResult = nullptr;

					// 이미 보관 중인 shared_ptr로 접근 (참조 카운트 변경 없음)
					auto start = std::chrono::steady_clock::now();
					for (size_t i = 0; i < iIterations; ++i)
					{
						pResult = sharedObject.get();
					}
					const double sharedAccessTime = std::chrono::duration<double, std::milli>(
						std::chrono::steady_clock::now() - start).count();

					// 보관 중인 핸들로 접근 (슬롯과 세대 번호 검사 포함)
					start = std::chrono::steady_clock::now();
					for (size_t i = 0; i < iIterations; ++i)
					{
						pResult = game.GetGameObjectByHandle(handle);
					}
					const double handleAccessTime = std::chrono::duration<double, std::milli>(
						std::chrono::steady_clock::now() - start).count();

					// shared_ptr를 복사한 뒤 접근 (반복마다 참조 카운트 증가와 감소)
					start = std::chrono::steady_clock::now();
					for (size_t i = 0; i < iIterations; ++i)
					{
						auto reference = sharedObject;
						pResult = reference.get();
					}
					const double sharedCopyTime = std::chrono::duration<double, std::milli>(
						std::chrono::steady_clock::now() - start).count();

					// 핸들을 복사한 뒤 접근
					start = std::chrono::steady_clock::now();
					for (size_t i = 0; i < iIterations; ++i)
					{
						auto reference = handle;
						pResult = game.GetGameObjectByHandle(reference);
					}
					const double handleCopyTime = std::chrono::duration<double, std::milli>(
						std::chrono::steady_clock::now() - start).count();

					std::wostringstream result;
					result << std::fixed << std::setprecision(3)
						<< L"shared_ptr 접근: " << sharedAccessTime << L" ms\n"
						<< L"핸들 조회: " << handleAccessTime << L" ms\n\n"
						<< L"shared_ptr 복사 + 접근: " << sharedCopyTime << L" ms\n"
						<< L"핸들 복사 + 조회: " << handleCopyTime << L" ms";
					MessageBoxW(nullptr, result.str().c_str(), L"shared_ptr / 핸들 비교 - 100만 회", MB_OK);
				}
			}
#pragma endregion

			// dynamic_cast vs static_cast benchmark 
			// dynamic_cast: 472ms, static_cast: 41ms
			if constexpr (false)
			{
				E::CGameObject* volatile val = E::CGameInstance::Get().GetGameObjectByHandle(uiCam.value());
				{
					auto start = std::chrono::high_resolution_clock::now();
					{
						E::CUICamera* volatile sink = nullptr;
						for (size_t i = 0; i < 10'000'000; ++i)
						{
							sink = Engine::Cast<E::CUICamera>(val);
						}
					}
					auto end = std::chrono::high_resolution_clock::now();
					auto cost = std::chrono::duration<double, std::milli>(end - start).count();
					MSG_BOX_STR(std::to_wstring(cost).c_str());
				}
				{
					auto start = std::chrono::high_resolution_clock::now();
					{
						E::CUICamera* volatile sink = nullptr;
						for (size_t i = 0; i < 10'000'000; ++i)
						{
							if (val->IsA(E::CUICamera::StaticType))
							{
								sink = static_cast<E::CUICamera*>(val);
							}
							else
							{
								sink = nullptr;
							}
						}
					}
					auto end = std::chrono::high_resolution_clock::now();
					auto cost = std::chrono::duration<double, std::milli>(end - start).count();
					MSG_BOX_STR(std::to_wstring(cost).c_str());
				}
			}
			{
				const auto* t = E::CGameInstance::GetConst().GetGameObjectByHandleT<E::CUICamera>(uiCam.value());

				auto* t2 = E::CGameInstance::Get().GetGameObjectByHandleT<E::CUICamera>(uiCam.value());
			}
		}


	}

	GET_SINGLE(UIManager)->CreateFadeOut(1.f, 5.f);

	return S_OK;
}

void CLevelLogo::Update(E::_float fTimeDelta)
{
	if (!m_VideoQue)
	{
		m_Video = GET_SINGLE(UIManager)->LoadPrefab("LogoVideo").front();
		static_cast<CVideoObject*>(SafeGetOBJ(m_Video))->SetPath(L"./Resources/SampleClient/Textures/UI/Video/CIN_HL.avi");

		//CHandle hBG = GET_SINGLE(UIManager)->LoadPrefab("BlackBG").front();
		//PlayFadeOutDelete(hBG);

		m_Logo = GET_SINGLE(UIManager)->LoadPrefab("Logo").front();
		SafeGetOBJ(m_Logo)->SetAlpha(0.f);
		if (auto* logo = E::CGameInstance::Get().
			GetGameObjectByHandleT<CTextureUI>(m_Logo))
		{
			logo->SetLogoSparkle(9.f, 3.f);
			const CHandle logoHandle = m_Logo;
			logo->Appear = [this, logoHandle](CUIObject*)
			{
				if (auto* currentLogo = GetSafeUI(logoHandle))
					currentLogo->SetAlpha(0.f);
				PlayFadeInSacleUp(logoHandle, 9.f, 5.f);
			};
		}

		m_VideoQue = true;

		{
			m_SoundId = E::CGameInstance::Get().GetSoundManager()->Play2D("./Resources/SampleClient/Sound/UI/Hedwings.mp3", SOUND_PLAY_DESC{
					.sBusID = SOUND_BUS::UI,
					.fVolume = 0.3f,
					.fPitch = 1.f,
					.iPriority = 64,
					.bLoop = false
				});
		}
	}

	if(!m_ChangeScene)
		m_SceneChangeTimer += fTimeDelta;

	if (!m_isLogoDelete && m_SceneChangeTimer > 17.f)
	{
		PlayFadeOutDelete(m_Logo, 0.f, 3.f);
		m_isLogoDelete = true;
	}
		

	if (!m_ChangeScene && E::CGameInstance::Get().KeyDown(DIK_SPACE))
	{
		CHandle hBG = GET_SINGLE(UIManager)->LoadPrefab("BlackBG").front();
		GetSafeUI(hBG)->SetAlpha(0.f);
		PlayFadeInChange(hBG);
		m_ChangeScene = true;
	}
	else if (!m_ChangeScene && m_SceneChangeTimer > 17.8f)
	{
		CHandle hBG = GET_SINGLE(UIManager)->LoadPrefab("BlackBG").front();
		GetSafeUI(hBG)->SetAlpha(0.f);
		PlayFadeInChange(hBG);

		m_SceneChangeTimer = 0.f;
		m_ChangeScene = true;
	}
		

}

HRESULT CLevelLogo::Render()
{
	return S_OK;
}

void CLevelLogo::UpdateGUI()
{
	ImGui::Begin("LEVEL: CLevel_Logo");
	ImGui::End();
}

void CLevelLogo::FrameStart(E::_float fTimeDelta)
{

}

void CLevelLogo::PlayFadeOutDelete(CHandle pHandle, float delay, float playtime)
{
	CUIObject* pBtn = SafeGetOBJ(pHandle);
	auto pTween = pBtn->GetTweenCom();

	pBtn->SetInputLcok(true);

	_float Alpah = pBtn->GetAlpha();

	pTween->PlayTween(1.f, 0.f, 5.f,
		[pBtn](float currentValue) {
			pBtn->SetAlpha(currentValue);
		}, [pHandle]() {
			if (auto pObj = GetSafeUI(pHandle)) GET_SINGLE(UIManager)->DeleteUIRecursive(pHandle);
			}, EEaseType::EaseOutQuad, 1.f);
}

void CLevelLogo::PlayFadeIn(CHandle pHandle, float delay, float playtime)
{
	CUIObject* pBtn = SafeGetOBJ(pHandle);
	auto pTween = pBtn->GetTweenCom();

	pBtn->SetInputLcok(true);

	_float Alpah = pBtn->GetAlpha();
	_float scaleRatio = pBtn->GetScaleRatio();

	pTween->PlayTween(0.f, 1.f, playtime,
		[pBtn](float currentValue) {
			pBtn->SetAlpha(currentValue);
		}, nullptr, EEaseType::EaseOutQuad, delay);
}

void CLevelLogo::PlayFadeInSacleUp(CHandle pHandle, float delay, float playtime)
{
	CUIObject* pBtn = SafeGetOBJ(pHandle);
	auto pTween = pBtn->GetTweenCom();

	pBtn->SetInputLcok(true);

	_float Alpah = pBtn->GetAlpha();
	_float scaleRatio = pBtn->GetScaleRatio();

	pTween->PlayTween(0.8f, scaleRatio, playtime,
		[pHandle](float currentValue) {
			if (auto pObj = GetSafeUI(pHandle))
			{
				pObj->SetScaleRatio(currentValue);
				pObj->CalcUICoord();
			}
		}, nullptr, EEaseType::EaseOutQuad, delay);

	pTween->PlayTween(0.f, 1.f, playtime,
		[pBtn](float currentValue) {
			pBtn->SetAlpha(currentValue);
		}, nullptr, EEaseType::EaseOutQuad, delay);
}

void CLevelLogo::PlayFadeInChange(CHandle pHandle, float delay, float playtime)
{
	CUIObject* pBtn = SafeGetOBJ(pHandle);
	auto pTween = pBtn->GetTweenCom();

	pBtn->SetInputLcok(true);

	_float Alpah = pBtn->GetAlpha();

	pTween->PlayTween(0.f, 1.f, playtime,
		[pBtn](float currentValue) {
			pBtn->SetAlpha(currentValue);
		}, nullptr, EEaseType::EaseOutQuad, delay);

	pTween->PlayTween(0.f, 1.f, playtime,
		[pBtn](float currentValue) {
			pBtn->SetAlpha(currentValue);
		}, [pHandle, this]() {
			Engine::CGameInstance::Get().ChangeLevel(
				CLevelLoading::Create(E::CGameInstance::Get().GetGraphicDevice(), E::CGameInstance::Get().GetGraphicDeviceContext(), LEVEL::CHARLES_ROOKWOOD));
			}, EEaseType::EaseOutQuad, delay);
}

HRESULT CLevelLogo::StopBGM()
{
	auto* pSoundManager = CGameInstance::Get().GetSoundManager();
	if (pSoundManager == nullptr ||
		!pSoundManager->FadeOutAndStop(m_SoundId, 1.f))
		return E_FAIL;

	m_SoundId = INVALID_SOUND_ID;

	return S_OK;
}

Engine::UPtr<CLevelLogo> CLevelLogo::Create()
{
	auto pInstance = Engine::UPtr<CLevelLogo>(new CLevelLogo{});
	pInstance->SetDeferredInitialization();
	return pInstance;
}

void CLevelLogo::Free()
{
	StopBGM();
	CLevel::Free();
}
