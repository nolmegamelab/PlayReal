# animation graph 

Engine/Source/Editor/AnimGraph/ 에 구현되어 있다. Editor에서 편집하고 
실행 시간에 따로 실행하는 건가? 

일단, 기능이 많다. 

## UAnimationGraph 

UEdGraph이다. 

## UAnimationStateGraph

UAnimationStateGraph는 UAnimationGraph이다. 

UAnimGraphNode_StateResult 를 갖는다. 

## UAnimationGraphSchema

UEdGraphSchema_K2 이다. 에디터에서 그래프는 스키마와 연결되나 보다. 

그래프의 행동을 제어하는 일정한 방향을 갖는 규약이 있으므로 스키마이다. 

SpawnNodeFromAsset(UAnimationAsset* Asset, GraphPosition, Graph 과 같은 함수가 있다. 

## Node 들

- AimOffsetLookAt 
- AnimDynamics
- ApplyAdditive 
- ApplyLimits
- ApplyMeshSpaceAdditive 
- AssetPlayerBase 
- Base 
- BlendBoneByChannel
- BlendListBase
- BlendListByBool 
- BlendListByEnum 
- BlendSpaceBase
- BlendSpaceEvaluator 
- BelanSpaceGraph
- BlendSpaceGraphBase
- BlendSpacePlayer 
- BlendDrivenController
- BlendSpaceSampleResult 
- BoneDrivenController 
- CCDIK
- ComponentToLocalSpace
- Contraint
- CopyBone
- CopyBoneDelta 
- CopyPoseFromMesh 
- CurveSource
- CustomProperty 
- CustomTransitionResult 
- Fabrik 
- HandIKRetargeting 
- IdentityPose
- Inertialization 
- LayerdBoneBlend
- LegIK 
- LinkedAnimGraph
- LinkedAnimGraphBase
- LinkedAnimLayer
- LinkedInputPose
- LocalRefPose
- LocalToComponentSpace
- LookAt
- MakeDynamicAdditive
- MeshRefPose
- Mirror
- ModifyBone
- ModifyCurve
- MultiWayBlend
- ObserveBone
- PoseBlendNode
- PoseByName
- PoseDriver
- PoseHandler
- PoseSnapshot
- RandomPlayer
- RefPoseBase
- ResetRoot
- RigidBody
- Root
- RotateRootBone
- RotationMultiplier
- RotationOffsetBlendSpace
- RotationOffsetBlendSpaceGraph
- SaveCachedPose
- ScaleChainLength
- SequenceEvaluator 
- SequencePlayer
- SkeletalControlBase
- Slot
- SplineIK
- SpringBone
- StateMachine
- StateMachineBase
- StateResult 
- Trail
- TransitionPoseEvaluator
- TransitionResult 
- TwsistCorrectiveNode
- TwoBoneIK
- TwoWayBlend
- UseCachedPose

애니메이션을 더 보기 전에 매시와 스켈 매시 구조와 사용을 이해한다. 

## FAnimNode_Base와 FAnimGraphNode_Base

앞은 런타임의 실행 기능, 뒤는 편집 기능을 갖는다. 두 가지로 동작한다. 
그러니까 애님 그래프를 사용해서 편집하고 구성된 내용을 실행하도록 한다. 

AnimationGraph는 스켈리톤에 대해 만든다. 그리고, 캐릭터에 지정할 수 있다. 

캐릭터의 스켈 매시 컴포넌트에 Anim Class로 지정하면 된다. 


## C++에서 애님 BP 변경

```c++
UAnimBlueprintGeneratedClass* armAnimBPGC = Cast<UAnimBlueprintGeneratedClass>(StaticLoadObject(UAnimBlueprintGeneratedClass::StaticClass(), NULL, *YourPathFStringVariable));
	if (armAnimBPGC)
	{
		ArmMesh->AnimBlueprintGeneratedClass = armAnimBPGC;
	}
~~~

또는 

```c++
static ConstructorHelpers::FObjectFinder<UAnimBlueprint> TmpMeshAnim( TEXT( "/MyGame/Anims/Char_Anim_BP.Char_Anim_BP" ) );
this->GetMesh()->SetAnimInstanceClass( TmpMeshAnim.Object->GetAnimBlueprintGeneratedClass() );
```

## UAnimInstance 

C++에서 구현하고 연결하면 다른 효과들을 얻을 수 있다. 

BP와 C++간의 예술적인 조화가 중요하다. 








