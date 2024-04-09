// 기존 코드에서 어떻게 UI 시스템을 개선할 수 있는지에 대한 예시를 보여줍니다.
// 이 예시는 실제로 동작하는 코드가 아니며, 이해를 돕기 위한 가상의 코드입니다. 
//
// 기존 코드에선 HUD에 종속적인 위젯을 생성하고, 위젯에 접근해 이벤트를 바인딩하는 방식으로 동작합니다.
void UUISomeExampleWidget::OpenSimpleYesNoPopup()
{
    AHUD* HUD = Cast<AHUD>(GetOwningPlayer()->GetHUD());
    if (HUD != nullptr)
    {
        UMessageBoxWidget* MessageWidget = HUD->MessageBoxOKandCANCEL(TEXT("UIText_Notice"), TEXT("PopupText_ExitParty"), TEXT(""), TEXT("Button_Ok"), TEXT("Button_Cancel"));
        if (MessageWidget != nullptr)
        {
            if (MessageWidget->GetButtonOk() != nullptr)
            {
                if (MessageWidget->GetButtonOk()->OnClicked.Contains(this, TEXT("OnClickedMessageLeaveParty")) == false)
                {
                    MessageWidget->GetButtonOk()->OnClicked.AddDynamic(this, &UUISomeExampleWidget::OnClickedMessageLeaveParty);
                }
            }

            if (MessageWidget->GetButtonCancel() != nullptr)
            {
                if (MessageWidget->GetButtonCancel()->OnClicked.Contains(this, TEXT("OnClickedCloseMessageBox")) == false)
                {
                    MessageWidget->GetButtonCancel()->OnClicked.AddDynamic(this, &UUISomeExampleWidget::OnClickedCloseMessageBox);
                }
            }
        }
    }
}


// 개선된 코드에서는 UI 시스템을 통해 팝업을 열고, 팝업에 필요한 데이터를 전달하는 방식으로 동작합니다.
// 이는 Caller와 Callee 사이의 의존성을 줄이고, 코드의 가독성을 높이는 장점이 있습니다.
void UUISomeExampleWidget::OpenSimpleYesNoPopup()
{
    PopupOpen(EUI::Popup_YesNo)->InitWith<UYesNoPopupWidgetArg>([this](auto Arg)
    {
        Arg->StringIdTitle = TEXT("UIText_Notice");
        Arg->StringIdMessage = TEXT("PopupText_ExitParty");
        Arg->StringIdYes = TEXT("Button_Ok");
        Arg->StringIdNo = TEXT("Button_Cancel");
        Arg->OnClickedYes.AddUniqueDynamic(this, &UUISomeExampleWidget::OnClickedMessageLeaveParty);
        Arg->OnClickedNo.AddUniqueDynamic(this, &UUISomeExampleWidget::OnClickedCloseMessageBox);
    });
}
