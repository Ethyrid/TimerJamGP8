#include "TimeBonusPoint.h"
#include "Components/BoxComponent.h"
#include "MyPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"  // Incluir este encabezado para ACharacter

// Constructor
ATimeBonusPoint::ATimeBonusPoint()
{
	// Inicializa el TriggerBox
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;

	// Configura el Trigger para que detecte superposiciones
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	TriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	TriggerBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	// Bind de la función de superposición
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ATimeBonusPoint::OnOverlapBegin);
}

// Se llama cuando el juego comienza
void ATimeBonusPoint::BeginPlay()
{
	Super::BeginPlay();
}

// Se llama cada frame
void ATimeBonusPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Función que se llama cuando otro actor entra en el TriggerBox
void ATimeBonusPoint::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	if (PlayerController && OtherActor->IsA(ACharacter::StaticClass()))
	{
		PlayerController->AddTimeBonus();
		Destroy(); // Destruye el punto de bonificación después de ser usado
	}
}

