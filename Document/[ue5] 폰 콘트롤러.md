
# 폰 콘트롤러 

Engine/Classes/GameFramework/ 에 Pawn이 있다. 

Engine/Classes에는 다음과 같은 것들이 있다. 
- AI, Animation, Atmosphere, Audio, Camera, Components, Curves, 
- DataDrivenCVars, Debug, DeviceProfiles, Distributions 
- EdGraph, EditorFramework, Engine, Exporters
- GameFramework 
- Interfaces, Intrinsic
- Kismet
- Layers, Lightmass
- Materials, Matine, MeshVertexPainter
- PacketHandlers, Particles, PhysicalMaterials, PhysicsEngine, PhysicsField
- Slate, Sound
- Tests 
- VectorField, Vehicles, VisualLogger, VT

Editor, Runtime, ThirdParty로 구성된 폴더 중 Runtime/Engine 폴더로 있다. 
Runtime이 게임의 실행에 관한 모든 것이고, Core, CoreObject, RenderCore, Renderer, RHI 등 
다른 중요 기능들이 Runtime에 모두 있다. 

GameFramework 중심으로 먼저 이해하면서, Slate를 포함한 GUI, NavMesh와 Physics, 
파티클, 애님 등 표현의 세부로 들어간다. 

매일 매일 언리얼 안에서 살면서 필요한 것들을 찾아서 익혀 나간다면 매우 익숙한 
엔진을 하나 얻게 되고 그 안에서 할 수 있는 제품들을 만들 수 있다. 


## AActor 

## FWeakObjectPtr 

264 라인의 클래스이다. 

```c++
(*this) = nullptr;
```

생성자에서 위와 같이 하면 this는 어떻게 되는가? 

GUObjectArray에서 찾는다. GUObjectArray는 FChunkedFixedUObjectArray
배열에서 찾으므로 빠른데 쓰레드 안전 문제가 있다. 게임 플레이 쓰레드 하나에서 
실행하는 경우에만 사용해야 한다.

UObject에 대해 GC를 막지 않고 참조를 갖고 싶을 때 사용한다. 따라서, 아주 많이 
사용할 수 있을 듯 하다. 

## ObjectPtr / TObjectPtr

ObjectHandle과 함께 UObject에 대한 포인터를 갖는다. 결국 타잎 캐스팅을 사용하는데 
이를 둘러싸서 좀 더 안전하게 사용하는 목적을 갖는다. 



## TDelegate / TMulticastDelegate

함수 포인터, 멤버 함수, 람다, UFunction, UObject로 delegate를 구성할 수 있게 한다. 
사용법을 잘 익혀서 익숙해지는 게 중요하다. 코드 구현 자체는 MPL이라 복잡하다. 

템플릿 프로그래밍을 잘 하면 좋겠다. 부럽.

액터에는 많은 유용한 델리기트들이 있다. 

## TSizedInlineAllocator 

로컬 변수로 생성하면 스택 메모리를 사용한다는 아이디어로 TInlineComponentArray를 구현한다. 
TInlineComponentArray는 일정 개수를 스택 메모리를 사용하여 보관하는 배열이다. 

## 초기화 순서 

AActor::BeginPlay()가 레벨 로딩 후 게임이 플레이 가능할 때 불린다. 특별한 경우가 아니면 
시작 지점으로 볼 수 있다. 

툴 제작을 할 때는 좀 다르게 접근해야 한다. 

## UObject

AActor의 기반 클래스이고 GC와 리플렉션이 필요한 모든 클래스가 상속 받는다. 
GC와 Reflection, Blueprint의 기반이다. 내부적인 구현은 java vm, .net 런타임과 유사하나
IL을 사용하지 않으므로 다르다. C++의 UFunction, UProperty, UClass 등으로 구성한다. 

UPackage를 사용하여 serialize하여 저장하고 로딩한다. 

## FActorTickFunction 

PrimaryActorTick. struct이고 ExecuteTick 함수를 갖는다. 

## Replication 

언리얼은 예전부터 복제 기반 동기화를 사용했다. 현재는 관심사가 아니고, 이벤트 기반 동기화를 
사용하는데 익숙하므로 쓰게 될 경우 많이 헤맬 듯. 

## 비트 플래그 

언리얼 특성은 비트 플래그를 상당히 많이 갖고 있다는 점이다. 이에 따라 행동이 달라지므로 
필수적인 플래그들은 지속적으로 알아가야 한다. 

 ## std:decay

http://egloos.zum.com/sweeper/v/3213836

암묵적 값 타잎 변환이다. 테스트 코드의 예시가 의미하는 것이다. 개념적으로 정리된 암묵적 변환을 
참고한다. 

https://stackoverflow.com/questions/25732386/what-is-stddecay-and-when-it-should-be-used

이런 걸 다 찾아서 추가하는 사람들은 대단하다. 

## std::declval 

https://modoocode.com/294


https://stackoverflow.com/questions/20303250/is-there-a-reason-declval-returns-add-rvalue-reference-instead-of-add-lvalue-ref

rvalue 참조를 추가하여 타잎 정보를 decltype에 넘기면서 실제 오브젝트는 생성하지 않는다. 
타잎 정보만 오브젝트 없이 전달한다. 


## 게임 기능 

- 위치 
  - K2_SetActorLocation, K2_GetActorLocation,  GetActorForwardVector 

- 컴포넌트 
  - 생성과 얻기. 
   
- 다른 액터 
  - 루트 컴포넌트를 붙이기, 떼기.

## TSharedRef / TSharedPtr

TSharedRef와 TSharedPtr의 차이는 Ref의 경우 참조처럼 non-nullable이다. 실제 링크는 포인터로 
갖고 있고 non-null invariant를 유지한다. 

UObject 계열은 제외한다. UObject들에 대한 포인터는 TObjectPtr을 사용한다. 


## 엔진 API 문서 

분류가 잘 되어 있어 실제 활용시 보기가 편하다. 

언리얼 내에 GUI를 갖는 API 조회 기능이 가치가 있을까? 직접적으로 개발에 도움이 될 만한 
도구면 더 좋을 듯 하다. 

직접 익숙해질 때까지 보고 쓰고 또 보고 하는 게 좋겠다. 하면서 일반화된 구조를 도구화 할 수 있다면
그렇게 한다. 라이브 doxygen 같은 개념도 괜찮아 보인다. clang으로 제대로 파싱해서 찾아도 되지 않을까?

## Fn: BecomeViewTarget

K2_BecomeViewTarget을 호출하는데 특별한 언급이 없다. 아마도 BP로 호출하는 매개체로 
사용하는 것으로 보인다. K2_가 Kismet2로 보인다. 

## Fn: GetCameraView 

오래된 카메라 제어 관련 개념들. 
- Fov
  - 핀홀 카메라의 렌즈 + 초점 거리에 따른 시야 범위
  
- AspectRatio
  - width / height

## TSubclassOf<T>

UClass나  FField의 하위 클래스에 대한 클래스 타잎을 갖고 있는 클래스이다. 
둘을 통합하여 처리하기위한 템플릿 마법이다. 

## 컴포넌트 순회 

ForEachComponent 들 

## TSet 

개념들. 이 길이 나의 길이다. 몇 년 남지 않은 시간을 잘 보내자. 

https://docs.unrealengine.com/4.27/ko/ProgrammingAndScripting/ProgrammingWithCPP/UnrealArchitecture/TSet/

## AController

APawn과 게임 이벤트 간의 간접층을 만들어서 필요한 규칙과 행동을 구현할 수 있는 층을 준다. 
이렇게 하면 APawn의 상속 계층이 아닌 AController의 상속 계층으로 게임 기능을 구현할 수 있다. 

APawn이 외관 중심의 기능 서비스를 안정적으로 제공하고 콘트롤러가 규칙을 구현하게 한다. 

- APlayerState PlayerState
- AActor StartSpot 
- FInstigatedAnyDamageSignature 
- FOnPossessedPawnChanged
- StateName
- USceneComponent TransformComponent 
- FRotator ControlRotation
- LineOfSightTo 
  - CollisionQuery를 사용하여 시각 처리하는 부분

429 라인의 작은 클래스이다. 액터를 상속해서 그렇다. 

## APawn 

- BaseEyeHeight : 직접 해봐야 알 수 있는 값들 
- UNavMovementComponent
  - SetPathFollowingAgent
  - SetFixedBrakingDistance
- CreatePlayerInputComponent(), SetupPlayerInputComponent()
  - Controller와 함께 입력 처리 
- AddMovementInput

## ACharacter

- TObjectPtr<USkeletalMeshComponent> Mesh 
- TObjectPtr<UCharacterMovementComponent> CharacterMovement
- TObjectPtr<UCapsuleComponent> CapsuleComponent 

이동을 이해하려면 CharacterMovementComponent와 Character를 자세히 봐야 한다. 
여기부터는 실체가 있어 게임에서 사용할 수 있다. 

실제 게임을 만들 때는 여기서 상속 받거나 유사한 정도의 클래스를 만들어
기반 클래스로 사용한다. 

