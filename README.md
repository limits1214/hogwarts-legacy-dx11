<div align="center">

# Hogwarts Legacy Clone

<img src="docs/media/hogwarts-legacy-key-art.jpg" width="620" alt="Hogwarts Legacy main key art">

### C++20 · DirectX 11 Custom Engine · 7인 팀 프로젝트

**자체 제작 엔진으로 구현한 3D 액션 RPG 《호그와트 레거시》 모작**

</div>

## 시연영상

[영상 포트폴리오 보기](https://www.youtube.com/watch?v=KKQKjYQcRwg)

임성윤 담당 구간: [**02:00~17:00 — 프레임워크 및 물리 구현**](https://www.youtube.com/watch?v=KKQKjYQcRwg&t=120)

## 프로젝트 정보

| 항목 | 내용 |
| --- | --- |
| 장르 | 3인칭 액션 RPG |
| 개발 기간 | 2026.06.30 ~ 2026.08.30 |
| 개발 인원 | 7명 |
| 플랫폼 | Windows x64 |
| 개발 환경 | Visual Studio 2022 |
| 제작 범위 | Engine · Client · Map Editor · Asset Pipeline |
| 기술 스택 | • C++20 · HLSL<br>• DirectX 11 · HBAO+<br>• PhysX 5.6.1 · NvCloth<br>• Recast/Detour<br>• FMOD<br>• Dear ImGui · ImGuizmo · Assimp · Tracy · vcpkg |

## 주요 콘텐츠

- Hogwarts·Hogsmeade 월드 탐험과 NPC 상호작용
- Accio, Depulso, Descendo, Confringo, Bombarda 기반 주문 전투
- Pensieve Guardian·Ranrok Dragon 보스전
- 빗자루 비행과 코인 타임어택
- 물리 기반 Summoner's Court 미니게임
- 상점·퀘스트·대화·시네마틱·사운드 시스템

## 담당 파트

<table>
  <thead>
    <tr>
      <th>팀원</th>
      <th>담당 파트</th>
      <th>구현 내용</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>
        <a href="https://github.com/EnoughKK"><strong>EnoughKK</strong></a>
      </td>
      <td>UI · UI Tools</td>
      <td>
        <strong>핵심 시스템</strong><br>
        • UIManager·UIController<br>
        • UI Prefab·Flipbook·Tween<br>
        <br>
        <strong>콘텐츠 구현</strong><br>
        • HUD·스킬 슬롯·미니맵·몬스터 HP<br>
        • 로딩·사망·페이드·상점·대화·퀘스트·미니게임 UI<br>
        <br>
        <strong>툴</strong><br>
        • UI Editor
      </td>
    </tr>
    <tr>
      <td>
        <a href="https://github.com/ForestMS1"><strong>ForestMS1</strong></a>
      </td>
      <td>World · Map Tools</td>
      <td>
        <strong>핵심 시스템</strong><br>
        • Chunk Streaming·Instancing<br>
        • GPU Frustum·Hi-Z Culling·Indirect Draw<br>
        <br>
        <strong>콘텐츠 구현</strong><br>
        • Hogwarts·Hogsmeade 월드 제작 기반<br>
        • Cinematic·Camera 시스템과 비행 콘텐츠 기반<br>
        <br>
        <strong>툴</strong><br>
        • Map Editor
      </td>
    </tr>
    <tr>
      <td>
        <a href="https://github.com/gnffk"><strong>gnffk</strong></a>
      </td>
      <td>Player · Animation</td>
      <td>
        <strong>핵심 시스템</strong><br>
        • Animator·GPU Skinning<br>
        • Root Motion·Montage·Socket·Blending<br>
        <br>
        <strong>콘텐츠 구현</strong><br>
        • 플레이어 FSM·이동·전투·주문·타기팅<br>
        • 빗자루 비행·Foot IK·NPC 상호작용<br>
        <br>
        <strong>툴</strong><br>
        • Animation Editor
      </td>
    </tr>
    <tr>
      <td>
        <a href="https://github.com/lcjune816"><strong>lcjune816</strong></a>
      </td>
      <td>AI · Enemy/Boss</td>
      <td>
        <strong>핵심 시스템</strong><br>
        • Behavior Tree·Blackboard<br>
        • 공통 몬스터 전투 AI<br>
        <br>
        <strong>콘텐츠 구현</strong><br>
        • 거미·트롤·NPC·동물 행동<br>
        • Pensieve Guardian·Ranrok Dragon 전투 패턴<br>
        <br>
        <strong>툴</strong><br>
        • Behavior Tree Node Editor
      </td>
    </tr>
    <tr>
      <td>
        <a href="https://github.com/limits1214"><strong>limits1214</strong></a> · 임성윤
      </td>
      <td>Framework · Physics</td>
      <td>
        <strong>핵심 시스템</strong><br>
        • 객체 생명주기·Generation Handle·Object Pool<br>
        • Fixed Update·Deferred Destruction·PhysX 컴포넌트 계층<br>
        <br>
        <strong>콘텐츠 구현</strong><br>
        • Summoner's Court 경기 시스템<br>
        • Physics Door·Ragdoll·물리 Prop<br>
        <br>
        <strong>툴</strong><br>
        • Physics Authoring Tools
      </td>
    </tr>
    <tr>
      <td>
        <a href="https://github.com/Lung-Ji"><strong>Lung-Ji</strong></a>
      </td>
      <td>Shader · Lighting</td>
      <td>
        <strong>핵심 시스템</strong><br>
        • Deferred PBR·Renderer Pipeline<br>
        • Light·Shadow·CSM·HBAO·Post Process<br>
        <br>
        <strong>콘텐츠 구현</strong><br>
        • Volumetric Fog·Cloud·God Ray<br>
        • Bloom·TAA·Radial Blur·레벨 조명<br>
        <br>
        <strong>툴</strong><br>
        • Light Placement Editor
      </td>
    </tr>
    <tr>
      <td>
        <a href="https://github.com/sungmin2ee"><strong>sungmin2ee</strong></a>
      </td>
      <td>Effect · Particle</td>
      <td>
        <strong>핵심 시스템</strong><br>
        • Effect·Particle Manager<br>
        • CPU/GPU Particle·Beam·Trail<br>
        <br>
        <strong>콘텐츠 구현</strong><br>
        • Particle Shader·Pattern·렌더 최적화<br>
        • 플레이어 주문·보스·월드 이펙트<br>
        <br>
        <strong>툴</strong><br>
        • Particle Effect Editor
      </td>
    </tr>
  </tbody>
</table>

## 리소스 다운로드 및 실행 준비

게임 실행에 필요한 리소스와 PhysX 라이브러리는 소스 저장소와 별도로 제공합니다.

[리소스 다운로드 — Google Drive](https://drive.google.com/drive/folders/1pgsmgKaIk12h-sKiSJaJCKi6S4Q8eorg?usp=sharing)

| 파일 | 내용 |
| --- | --- |
| `physx-5.6.1.zip` | 빌드에 필요한 PhysX 헤더·라이브러리·DLL |
| `LastAsset.7z` | 게임 리소스 및 추가 배치 파일 |
| `HogwartVideo.zip` | 게임 내 영상 리소스 — 선택 사항(Optional), 업로드 중 |

### 1. 게임 리소스 배치

`LastAsset.7z`를 압축 해제합니다.

압축 해제된 내용 중 `Client`, `Engine`, `SampleClient`, `json` 등의 폴더가 함께 있는 위치를 **리소스 루트**로 사용합니다. 압축 해제 과정에서 생성되는 상위 폴더와 혼동하지 않도록 주의해 주세요.

이 가이드에서는 다음 위치를 리소스 루트로 가정합니다.

```text
C:\Hogwarts\Resources\
├─ Client\
├─ Engine\
├─ SampleClient\
├─ PhysX\
├─ NvCloth\
└─ json\
```

폴더 이름과 내부 경로는 유지해야 합니다. `SampleClient` 폴더도 실제 게임에서 사용하는 리소스를 포함합니다.

### 2. 리소스 심볼릭 링크 생성

게임은 `Client\Bin\Resources`를 기준으로 리소스를 읽습니다. 해당 경로가 앞에서 배치한 리소스 루트를 가리키도록 연결합니다.

**관리자 권한으로 명령 프롬프트(cmd)를 실행**하고 아래 명령을 입력합니다. 프로젝트와 리소스 경로는 본인의 환경에 맞게 변경해 주세요.

```bat
cd /d "C:\Hogwarts\JUSIN_160_FINAL_TEAM_PROJECT"

if not exist "Client\Bin" mkdir "Client\Bin"

mklink /D "Client\Bin\Resources" "C:\Hogwarts\Resources"
```

연결 후 다음 경로로 리소스에 접근할 수 있어야 합니다.

```text
프로젝트\Client\Bin\Resources\SampleClient\
프로젝트\Client\Bin\Resources\Engine\
프로젝트\Client\Bin\Resources\json\
```

- `Client\Bin\Resources`가 이미 존재하면 링크 생성이 실패합니다. 기존 폴더나 링크의 내용을 확인한 뒤 진행해 주세요.
- `Resources\Resources`처럼 폴더가 한 단계 더 들어가지 않도록 주의해 주세요.
- 심볼릭 링크 대신 리소스 루트의 내용을 실제 `Client\Bin\Resources` 폴더에 복사해도 됩니다.

### 3. PhysX 라이브러리 배치

`physx-5.6.1.zip`을 압축 해제하고 프로젝트의 `ThirdParty` 폴더에 배치합니다.

최종 경로가 다음과 같아야 합니다.

```text
프로젝트\ThirdParty\physx-5.6.1\
├─ include\
├─ bin_debug\
└─ bin_release\
```

`include`에는 헤더가, `bin_debug`와 `bin_release`에는 해당 구성의 라이브러리와 DLL이 있어야 합니다.

압축 해제 시 `physx-5.6.1\physx-5.6.1`처럼 폴더가 중복되지 않도록 확인해 주세요. PhysX DLL은 빌드 과정에서 `Client\Bin`으로 자동 복사됩니다.

### 4. 추가 파일 배치

`LastAsset.7z` 안의 `the last` 폴더에 있는 아래 두 파일을 지정된 위치에 복사합니다. 대상 폴더가 없으면 생성해 주세요.

| 파일 | 복사할 위치 |
| --- | --- |
| `HogsmeadePuddle.json` | `프로젝트\Client\Bin\DecalMaterials\HogsmeadePuddle.json` |
| `Shader_RWBFloor.hlsl` | `프로젝트\Client\Bin\ShaderFiles\Decal\Shader_RWBFloor.hlsl` |

각각 호그와트 월드의 물웅덩이 재질과 찰스 룩우드 보스맵의 바닥 셰이더에 사용됩니다.

이 파일들은 `Resources` 폴더 안이 아니라 **`Client\Bin` 아래의 지정된 폴더**에 배치해야 합니다.

### 5. 영상 리소스 배치 — 선택 사항(Optional)

영상 리소스는 게임 실행에 필수가 아닙니다. 배치하지 않으면 관련 영상은 재생되지 않으며, 이 단계는 건너뛰어도 됩니다.

영상 재생을 원하는 경우 `HogwartVideo.zip`의 업로드가 완료된 후 다운로드하여 압축을 해제합니다. 영상 파일을 다음 위치에 배치합니다.

```text
리소스 루트\SampleClient\Textures\UI\Video\
```

이 가이드의 예시 경로에서는 다음과 같습니다.

```text
C:\Hogwarts\Resources\SampleClient\Textures\UI\Video\
```

심볼릭 링크를 통해 게임에서는 아래 경로로 접근합니다.

```text
프로젝트\Client\Bin\Resources\SampleClient\Textures\UI\Video\
```

영상 파일의 이름은 유지해 주세요. `Video` 아래에 `HogwartVideo` 폴더를 추가로 넣지 말고, 영상 파일이 바로 위치하도록 배치합니다.

### 6. 빌드 및 실행

Visual Studio의 C++ 빌드 환경과 vcpkg 의존성 복원이 준비된 상태에서 진행합니다.

1. `MyProject.sln`을 엽니다.
2. 빌드 구성을 `Release`, 플랫폼을 `x64`로 선택합니다.
3. 시작 프로젝트를 `Client`로 설정합니다.
4. Engine과 Client를 빌드한 뒤 실행합니다.

실행 작업 폴더는 `Client\Bin`입니다. Visual Studio의 x64 실행 설정에는 해당 경로가 지정되어 있습니다.

> 이 가이드는 소스 프로젝트 전체를 유지한 상태에서 빌드·실행하는 기준입니다. 일부 셰이더가 엔진 소스 쪽의 공통 파일을 참조하므로, `Client\Bin`만 다른 위치로 옮기는 실행본 배포와는 구분됩니다.
