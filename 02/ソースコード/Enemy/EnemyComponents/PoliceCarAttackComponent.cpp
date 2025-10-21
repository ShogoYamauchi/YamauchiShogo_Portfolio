//--------------------------------------------------------------------
// �t�@�C�����FPoliceCarAttackComponent.cpp
// �T�v�@�@�@�F�p�g�J�[�𐧌䂷��N���X
// �쐬�ҁ@�@�F�R���@����
// �X�V���e�@�F2025/01/26	�N���X�̍쐬 
//--------------------------------------------------------------------

#include "PoliceCarAttackComponent.h"
#include "PoliceCar_Warning.h"

// �R���X�g���N�^
UPoliceCarAttackComponent::UPoliceCarAttackComponent()
	: _owner(UEnemyAttackComponent::GetOwner())
	, _currentSpeed()
	, _timer(0.0f)
	, _exitTimer(0.0f)
	, _appearTimer(0.0f)
	, _isAppear(0.0f)
{
	// ���t���[���A���̃N���X��Tick()���ĂԂ��ǂ��������߂�t���O
	// �K�v�ɉ����āA�p�t�H�[�}���X����̂��߂ɐ؂邱�Ƃ��ł���B
	PrimaryComponentTick.bCanEverTick = true;
}

// �Q�[���X�^�[�g���A�܂��͐������ɌĂ΂�鏈��
void UPoliceCarAttackComponent::BeginPlay()
{
	Super::BeginPlay();
	// �����ʒu���擾
	_initialLocation = _owner->GetActorLocation();
	// �ڕW�ʒu���擾
	_appearTargetLocation = _initialLocation + _forwardTargetLocation;
	// �x�����X�|�[��������
	APoliceCar_Warning* SpawnedWarning = GetWorld()->SpawnActor<APoliceCar_Warning>(_policeCar_WarningClass, _initialLocation + _warningActorSpawnLocation, FRotator::ZeroRotator);
}

// ���t���[������
void UPoliceCarAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// �o�ߎ��Ԍv��
	_timer += DeltaTime;

	// �o�ꂵ�Ă��Ȃ������珈��
	if (!_isAppear)
	{
		// �w�肵�����Ԍo�߂�����o�ꂳ����
		if (_appearStartTime <= _timer)
		{
			// �o�ꂳ����
			_appearAtLocation(DeltaTime);
		}
	}
	else
	{
		// �o�邵�Ă���w�肵�����Ԍo�߂�����ޏꂳ����
		if (_exitStartTime <= _timer)
		{
			// �ޏꂳ����
			_moveBackAndExit(DeltaTime);
		}
	}
	
}

// �֐����F_enterAtLocation
// �����F_deltaTime�F�P�t���[���ɂ�����b��
// �߂�l�F�Ȃ�
// ���e�F�^�[�Q�b�g�̍��W�܂ňړ����Ȃ���o�ꂷ��֐�
void UPoliceCarAttackComponent::_appearAtLocation(float deltaTime)
{
	if (!_owner) { /*UE_LOG(LogTemp, Warning, TEXT("PoliceCar / Failed To Acquire Owner"));*/ return;}		// �R���|�[�l���g�̃I�[�i�[�ł��� Actor �����邩�`�F�b�N

	FVector _currentLocation = _owner->GetActorLocation();   // ���݂̈ʒu��ݒ�

	// �o�ߎ��Ԃ��X�V
	_appearTimer += deltaTime;

	// �ړ����̏���
	if (_appearTimer < _appearDuration)
	{
		//UE_LOG(LogTemp, Log, TEXT("Helicopter is Moving"));
		// ���`�i�s�x���v�Z
		// �Ë�����
		float LinearAlpha = FMath::Clamp(_appearTimer / _appearDuration * 0.02f, 0.0f, 1.0f);

		// �C�[�W���O�֐���K�p
		// EaseAlpha��0�`1�͈̔͂Ɏ��߂�
		float EaseAlpha = FMath::Clamp(FMath::InterpEaseOut(0.0f, 1.0f, LinearAlpha, 2.0f), 0.0f, 1.0f);

		// �V�����ʒu���v�Z
		FVector NewLocation = FMath::Lerp(_currentLocation, _appearTargetLocation, EaseAlpha);

		// �V�����ʒu�ɃA�N�^�[���ړ�
		_owner->SetActorLocation(NewLocation);
	}
	else
	{
		_isAppear = true;	// �o�ꊮ��
		_timer = 0.0f;	// �^�C�}�[���Z�b�g
	}
}

// �֐����F_moveBackAndExit
// �����F_deltaTime�F�P�t���[���ɂ�����b��
// �߂�l�F�Ȃ�
// ���e�F��ނ����đޏꂳ����֐�
void UPoliceCarAttackComponent::_moveBackAndExit(float deltaTime)
{
	// �o�ߎ��Ԃ����Z
	_exitTimer += deltaTime;

	// ���݂̈ʒu���擾
	FVector _currentLocation = _owner->GetActorLocation();

	// ���Ԃ��o�߂��������ꍇ�̒���
	if (_exitTimer >= _exitDuration)
	{
		// �Ë�����
		_owner->Destroy();
	}

	// ���X�ɉ����������ԌW���i��F���Ԃ̓��ŉ����j
	float Alpha = FMath::Clamp(_exitTimer / _exitDuration, 0.0f, 1.0f);
	float AcceleratedAlpha = FMath::Pow(Alpha, _exitMoveSpeed);  // ���Ԃ̓��ŉ���

	// ���`��Ԃňʒu���v�Z
	FVector NewLocation = FMath::Lerp(_currentLocation, _initialLocation, AcceleratedAlpha);

	// �A�N�^�[�̈ʒu���X�V
	_owner->SetActorLocation(NewLocation);
}


// �U�����d�|����֐�(�e�̗\�������o���Ēe�𔭎˂���)
// �֐����FEnemyAttack 
// �����F�P�t���[���ɂ����鎞��
// ���e�F�x�@�̍U�����s���I�[�o�[���b�v�֐��@
void UPoliceCarAttackComponent::EnemyAttack(float deltaTime)
{
	;
}
