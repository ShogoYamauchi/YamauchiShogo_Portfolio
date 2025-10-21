//--------------------------------------------------------------------
// �t�@�C�����FEnemyAttackComponent.cpp
// �T�v�@�@�@�F�v���C���[�Ƀ_���[�W��^����R���|�[�l���g�N���X
// �쐬�ҁ@�@�F�R���@����
// �X�V���e�@�F2024/12/02	�N���X�̍쐬 
//--------------------------------------------------------------------

#include "EnemyAttackComponent.h"
#include "Components/SplineComponent.h"

// �R���X�g���N�^
UEnemyAttackComponent::UEnemyAttackComponent()
	: EnemyState(EnemyStatus::Idle)
{
	// ���t���[���A���̃N���X��Tick()���ĂԂ��ǂ��������߂�t���O
	// �K�v�ɉ����āA�p�t�H�[�}���X����̂��߂ɐ؂邱�Ƃ��ł���B
	PrimaryComponentTick.bCanEverTick = true;
}


// �Q�[���X�^�[�g���A�܂��͐������ɌĂ΂�鏈��
void UEnemyAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// ���t���[������
void UEnemyAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//// �֐����FGetEnemyPower
//// �����F�Ȃ�
//// �߂�l�F�G�̍U����
//// ���e�F�e�G�̍U���͂��擾���邽�߂̊֐�
//int UEnemyAttackComponent::GetEnemyPower()
//{
//	return _enemyPower;
//}

// �֐����FCanAttack
// �����F
// �߂�l�F�U���ł��邩�ǂ����̃t���O
// ���e�F�U���ł��邩�ǂ�����Ԃ��֐�
bool UEnemyAttackComponent::CanAttack() const
{
	return _isAttackAble;
}

// �֐����FEnemyAttack
// �����F�Ȃ�
// �߂�l�F�Ȃ�
// ���e�F�eEnemy�̍U���̏������Ăяo�����z(virtual)�֐�
void UEnemyAttackComponent::EnemyAttack(float deltaTime)
{
	// �y�f�o�b�O�p�z
	//UE_LOG(LogTemp, Log, TEXT("Invoke EnemyAttack()"));

	// �ݒ肵�Ă��Ȃ�
}	