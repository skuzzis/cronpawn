#if defined _cronpawn_inc
	#endinput
#endif

#define _cronpawn_inc

#define LOG_NONE                    0x00000000
#define LOG_ERROR                   0x00000500
#define LOG_WARNING                 0x08000000
#define LOG_DEBUG                   0x00000001

native cronpawn_SetLogLevel(loglevel = LOG_ERROR | LOG_WARNING);

native CronID:CreateCron(cron_name[], cron_settings[], callback[], args[], {Float,_}:...);
native DeleteCron(CronID:cronid);
native SuspendCron(CronID:cronid);
native UnsuspendCron(CronID:cronid);
native DoesCronExists(CronID:cronid);
native ExecuteCron(CronID:cronid, bool:bypassSuspend = false);