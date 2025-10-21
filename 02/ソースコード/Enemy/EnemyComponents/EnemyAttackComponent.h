//--------------------------------------------------------------------
// �t�@�C�����FEnemyAttackComponent.h
// �T�v�@�@�@�F�v���C���[�Ƀ_���[�W��^����R���|�[�l���g�N���X
// �쐬�ҁ@�@�F�R���@����
// �X�V���e�@�F2024/12/02	�N���X�̍쐬 
//--------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyAttackComponent.generated.h"

// �O���錾
class USplineComponent;

// �G�̃X�e�[�^�X��enum�^�Ő��䂷�� �Ë��ق�Ƃ�Enemy�N���X�ɐ錾������
UENUM(BlueprintType) // Blueprint�Ŏg�p�\�ɂ���}�N��
enum class EnemyStatus : uint8
{
	Idle UMETA(DisplayName = "Idle"),	// �ҋ@���
	Style UMETA(DisplayName = "Style"),	// �\�����
	Fire UMETA(DisplayName = "Fire"),	// ���C���
	Die UMETA(DisplayName = "Die"),		// ���S���
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROTOTYPE_API UEnemyAttackComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	// �Q�[���X�^�[�g���A�܂��͐������ɌĂ΂�鏈��
	virtual void BeginPlay() override;

public:
	// �R���X�g���N�^
	UEnemyAttackComponent();

	// ���t���[������
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadWrite, Category = "EnemyStatus")
	EnemyStatus EnemyState;	// �G�̃X�e�[�^�X�@�Ë��ق�Ƃ�Enemy�N���X�ɐ錾������

	bool _isAttackAble;	// �U���ł��邩�ǂ����̃t���O

	// �e�G�̍U�����Ăяo���֐�
	UFUNCTION()
	virtual void EnemyAttack(float _deltaTine);

	// �U���͂��擾����֐�
	virtual int GetAttackPower()const { return _enemyAttackPower; }

	// �U���ł��邩�ǂ����̃t���O��Ԃ��֐�
	bool CanAttack() const;

private:
	UPROPERTY(EditAnywhere)
	int _enemyAttackPower;	// �U����
};
