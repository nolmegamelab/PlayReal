# animation 

애니메이션은 게임을 만드는 기본 중의 기본이고 여전히 중요한 아트적인 도구이다. 

- skeletal mesh 
- animation sequence
- blend space
- animation blueprints
- state machine
- sequencer tool
  - character
  - character
  - effects
- control rig 
  - can be animated in sequencer

파티클은 직접 구현해봤기 때문에 이해하기가 더 쉽다. 애니메이션도 구현은 했으나 
언리얼 만큼 다양한 기능을 갖고 있지는 않았기 때문에 노력을 더 해야 한다. 

## USkinMeshComponent 

Engine/Classes/Components 폴더에 있다. 

- EBoneVisibilityStatus 
- EPhysBodyOp
- EVisibilityBasedAnimTickOption 
- EBoneSpaces
- FActiveMorphTarget
  - SkinMesh는 SkeletalMesh까지 가야 하나의 완전체이다. 
- FSkelMeshSkinWeightInfo
  - 12개를 최대로 Bone과 Weight를 갖는다. 
- FSkelMeshComponentLODInfo

UMeshComponent에서 상속 받는데 공통된 부분은 재질(Material)이 주된 것이다. 

USkeletalMesh를 갖는다. 

- USkeletalMesh 
- UMeshDeformer 
- UMeshDeformerInstance
- ComponentSpaceTransformsArray 

전체를 이해하려면 가장 간단한 애님시퀀스의 처리부터 봐야 한다. 
실제 애님은 GPU에서 계산하므로 해당 부분도 이해해야 한다. 
그리고, 완전한 애님은 스켈 매시 컴포넌트에서 이루어진다. 

## USkeletalMeshComponent 

## AnimTypes.h 

Bone이나 애님 데이터에 관한 정의가 들어 있다. 


## AnimationSequence

가장 기본적인 데이터이고 애님 커브의 보간과 본 적용으로 이루어진다. 변환 값들과 본 데이터가 쉐이더에 
전달되면 애님이 표현된다. 



## Animation Blend Space

생각보다 저수준의 구현을 갖는 걸로 보인다. BlendSpace를 활용하여 게임을 만든다는 뜻이다. 
블렌드 스페이스의 외부 제어에 대응하는 세부적인 움직임의 구현이 저수준이라는 뜻이다. 
따라서, 상위 개념을 만들어 통합하여 적용해야 한다. 

## Animation Montage 

RPG에 적합한 도구가 아닌가 싶다. 

## Animation Graph 



## Animation Sequencer







