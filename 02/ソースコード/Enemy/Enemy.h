//--------------------------------------------------------------------
// �t�@�C�����FEnemy.h
// �T�v�@�@�@�F�G�i�G�ɑ΂��ă_���[�W��^������́j�̍����N���X
// �쐬�ҁ@�@�F�R���@����
// �X�V���e�@�F2024/11/25	Enemy�N���X�̍쐬
//--------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Enemy.generated.h"

//	�O���錾
class USceneConponent;
class UEnemyAttackComponent;
class UEnemyDamagedComponent;
class UEnemyDeadComponent;
class UFlyAwayActorComponent;

UCLASS()
class PROTOTYPE_API AEnemy : public APawn
{
	GENERATED_BODY()

protected:
	// �Q�[���X�^�[�g���A�܂��͐������ɌĂ΂�鏈��
	virtual void BeginPlay() override;

public:
	// �R���X�g���N�^
	AEnemy();

	// ���t���[������
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int _hp;	// �̗�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Score;	// �X�R�A

private:

	UPROPERTY()
	TArray<UPrimitiveComponent*> _pCollisionComponent;		// �R���W�����R���|�[�l���g

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = EnemyComponent, meta = (AllowPrivateAccess = "true"))
	UEnemyAttackComponent* _pAttackComponent;		        // �U�����邽�߂̃R���|�[�l���g

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = EnemyComponent, meta = (AllowPrivateAccess = "true"))
	UEnemyDamagedComponent* _pDamagedComponent;		        // �_���[�W���󂯂邽�߂̃R���|�[�l���g

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = EnemyComponent, meta = (AllowPrivateAccess = "true"))
	UEnemyDeadComponent* _pDeadComponent;		            // ���Łi���ʁj���߂̃R���|�[�l���g

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = EnemyComponent, meta = (AllowPrivateAccess = "true"))
	UFlyAwayActorComponent* _pFlyAwayActorComponent;		// ������Ԃ��߂̃R���|�[�l���g


	// �Փ˂��n�߂����ɌĂяo���֐��i�����I�ڐG�͖����j
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// �f�o�b�O�p
	//UFUNCTION()
	//	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	//		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
