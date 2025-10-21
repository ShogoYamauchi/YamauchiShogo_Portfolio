//--------------------------------------------------------------------
// �t�@�C�����FHelicopterAttackComponent.h
// �T�v�@�@�@�F�w���R�v�^�[�i�G�j�̍U������R���|�[�l���g
// �쐬�ҁ@�@�F�R���@����
// �X�V���e�@�F2024/12/31	�N���X�̍쐬
//--------------------------------------------------------------------

#pragma once

#include "prototype/Interface/IBulletFactory.h"		// �e��ł֐�������C���^�[�t�F�[�X
#include "CoreMinimal.h"
#include "prototype/Stage/StageData.h"	// �Ë�����
#include "prototype/Stage/StageManager.h"	// �Ë�����
#include "EnemyAttackComponent.h"
#include "HelicopterAttackComponent.generated.h"

// �O���錾
class ULineControllerComponent;
class AEnemyBullet;
class USEManager;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROTOTYPE_API UHelicopterAttackComponent : public UEnemyAttackComponent, public IBulletFactory
{
	GENERATED_BODY()

protected:
	// �Q�[���X�^�[�g���A�܂��͐������ɌĂ΂�鏈��
	virtual void BeginPlay() override;

public:
	// �R���X�g���N�^
	UHelicopterAttackComponent();
	// ���t���[������
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// �e�G�̍U�����Ăяo���֐�
	void EnemyAttack(float _deltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* _playerActor;		// �v���C���[�̃A�N�^�[
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AEnemyBullet> EnemyBulletClass;	// �e�̐ݒ� (BP������eActor�̎w��)

	UFUNCTION()
	void DrawPredictionSplineWithCollision(float DeltaTime);	// �\�������o���֐�
	UFUNCTION()
	void SpawnBullet();	// �e���C���X�^���X������֐�

	void EndPlay(const EEndPlayReason::Type EndPlayReason);		// �w���R�v�^�[���폜���ꂽ���ɌĂԗp

	void SetMoveTargetNumber(int moveTargetNumber);	// �Ë�����

	// �U���͂��擾����֐�
	int GetAttackPower()const { return _policeAttackPower; }
private:

	UPROPERTY()
	TArray<AActor*> _pItems;	// �A�C�e�����ׂāi�W���G���E�}�O�l�b�g�E�񕜁j�i�[�p
	UPROPERTY()
	TArray<AActor*> _pSmogs;	// ���i�[�p

	UPROPERTY(EditAnywhere, Category = "MoveTargetActors")
	AActor* _moveTargetActors[3];	// �ړ��ڕW�A�N�^�[�̌��

	UPROPERTY()
	USEManager* _seManager;			// �T�E���h�}�l�[�W���[

	UPROPERTY(EditAnywhere)
	USoundBase* _rotorSound;		// �w���R�v�^�[�̉H�̉��i���[�^�[���j
	UPROPERTY(EditAnywhere)
	USoundBase* _gunSound;			// �x�@�̎ˌ���

	//UPROPERTY()
	AActor* _owner;				// �I�[�i�[�̃A�N�^�[
	UPROPERTY()
	AActor* _moveTargetActor;	// �ړ��ڕW�A�N�^�[

	UPROPERTY()
	ULineControllerComponent* _pLineControllerComponent;		// �\�������o�����߂̃R���|�[�l���g

	UPROPERTY(EditAnywhere)
	FVector _enemyBulletOffset;	// �e�̔��ˈʒu�̃I�t�Z�b�g

	UPROPERTY(EditAnywhere)
	float _canAttackTime;					// �o�����Ă����ʒu�Ɉړ����鎞��
	UPROPERTY(EditAnywhere)
	float _timeToAttack;					// �\�����o���܂ł̎���
	UPROPERTY(EditAnywhere)
	float _enemyAttackCooldown;				// ����ł�����ēx�v���C���[��_������
	UPROPERTY(EditAnywhere)
	float _predictionStopToFireInterval;	// �\�������~�܂��Ă��甭�C����܂ł̎���
	UPROPERTY(EditAnyWhere)
	float _timeToFire;						// ���ˊԊu(����)
	UPROPERTY(EditAnywhere)
	float _bulletSpeed;						// �e�̃X�s�[�h

	UPROPERTY(EditAnywhere)
	int _policeAttackPower;		// �U����

	FCollisionQueryParams _queryParamsToTrace;		// ��������N�G���p�����[�^�i�g���[�X�p�j

	FVector _startPointToDrawPrediction;	// �\�����̎n�_
	FVector _endPointToDrawPrediction;		// �\�����̏I�_
	FRotator _rotationToFire;				// �\�����Ƌ���łۂ̕����x�N�g��
	float _canAttackTimer;					// �^�C�}�[(�o�����Ă���\�������o���܂ł̎��Ԍv��)
	float _bulletTimer;						// �^�C�}�[(�\�������o���Ă��甭�˂���܂ł̎��Ԍv��)
	int _moveTargetNumber;					// �ړ��ڕW�̃A�N�^�[�i���o�[ �Ë�����
	bool _hasFired;							// ����ł������̃t���O

	// �ړ��ڕW�̃^�[�Q�b�g��ݒ肷��֐� StageBase�ŌĂяo���p
	void _setMoveTargetActor();

	// �n�_����I�_�ւ̕����x�N�g�����v�Z����֐�
	FRotator CalculateRotationByPoints(const FVector& StartPoint, const FVector& EndPoint);

	// �^�[�Q�b�g�̃|�C���g�܂ňړ�����֐�
	void _moveToTargetLocation(float _deltaTime);
};
