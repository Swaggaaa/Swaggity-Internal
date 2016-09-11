#include "Hooks.h"

VMTSwag* Hooks::Client;
VMTSwag* Hooks::ClientMode;
VMTSwag* Hooks::Events;
VMTSwag* Hooks::Surface;
VMTSwag* Hooks::VPanel;
VMTSwag* Hooks::D3D9;
CreateMoveFn oCreateMove;
OverrideViewFn oOverrideView;
FrameStageNotifyFn oFrameStageNotify;
PaintTraverseFn oPaintTraverse;
EndSceneFn oEndScene;
ResetFn oReset;