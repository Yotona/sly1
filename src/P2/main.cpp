#include <main.h>
#include <gs.h>
#include <joy.h>
#include <clock.h>
#include <ui.h>
#include <game.h>
#include <update.h>
#include <sw.h>
#include <render.h>
#include <frm.h>
#include <transition.h>
#include <mpeg.h>
#include <wipe.h>
#include <phasemem.h>
#include <spliceutils.h>
#include <stdio.h>
#include <stdlib.h>

// Build id is MMDD.HHMM
#define BUILD_ID __DATE__[0], __DATE__[1], __DATE__[3], __DATE__[4], __TIME__[0], __TIME__[1], __TIME__[3], __TIME__[4]
#define BUILD_YEAR __DATE__[7], __DATE__[8], __DATE__[9], __DATE__[10]
#define BUILD_USER getenv("USER")
#define BRX_VERSION 000

int main(int cphzArgs, char* aphzArgs[])
{
	// __main(); // from libgcc2
	g_chpzArgs = cphzArgs;
	g_aphzArgs = aphzArgs;

	Startup();

	while (true)
	{
		// todo: implement all these methods

		// Check if g_mpeg has an mpeg queued to be played
		if ((g_mpeg.oid_1 != OID_Unknown) && (g_wipe.wipes != WIPES_Idle))
		{
			//FlushFrames(1); // todo implement
			g_mpeg.ExecuteOids();
		}

		// Check if g_transition has a pending transition
		if (g_transition.m_fPending != 0)
		{
			//FlushFrames(1); // todo implement
			g_transition.Execute();
		}

		// Check AGAIN if g_mpeg has an mpeg queued (in case two were queued back-to-back)
		if ((g_mpeg.oid_2 != OID_Unknown) && (g_wipe.wipes != WIPES_Idle))
		{
			//FlushFrames(1); // todo implement
			g_mpeg.ExecuteOids();
		}

		// Call update functions
		UpdateJoy(&g_joy);
		UpdateCodes();
		//UpdateSave(&g_save);
		UpdateUi(&g_ui);
		UpdateGameState(g_clock.dt);

		// Render and draw current frame
		if (g_psw != NULL)
		{
			// Prepare to render frame
			SetupCm(g_pcm);
			OpenFrame();
			MarkClockTick(&g_clock);

			// This ends up calling UpdateSw down the line
			void* pv = g_psw + 0x54;
			if (pv != NULL)
			{
				//(*pv)(g_clock.dt);
			}

			// Render frame
			RenderSw(g_psw, g_pcm);
			RenderUi();

			// Draw frame
			DrawSw(g_psw, g_pcm);
			DrawUi();

			CloseFrame();
		}

		// Temp debug function just to show everything is running
		MainDebug();

		// Increment the global frame counter
		g_cframe += 1;
	}
}

void Startup()
{
	printf("Sly Cooper %x %s\n  Sly 1 Decompilation Team\nP2: %s %s\nBrx: %d\n\n", 0xA9, BUILD_YEAR, BUILD_ID, BUILD_USER, BRX_VERSION);
	SetPhase(PHASE_Startup);

	StartupSplice();

	// todo startup other game systems
	// ...

	ClearPhase(PHASE_Startup);
}

void MainDebug()
{
	// print current frame number
	printf("%d\r", g_cframe);
}
