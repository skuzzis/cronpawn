# Natives

Below will be an updated list of natives and functions.

```pawn
native cronpawn_SetLogLevel(loglevel = LOG_ERROR | LOG_WARNING);

native CronID:CreateCron(cron_name[], cron_settings[], callback[], args[], {Float,_}:...);
native DeleteCron(CronID:cronid);
native SuspendCron(CronID:cronid);
native UnsuspendCron(CronID:cronid);
native DoesCronExists(CronID:cronid);
native ExecuteCron(CronID:cronid, bool:bypassSuspend = false);
```

## External links

[Quick-Start](https://github.com/skuzzis/cronpawn/blob/master/pages/quick_start.md) - Quick-Start for Cronpawn.

[Examples](https://github.com/skuzzis/cronpawn/blob/master/pages/examples.md) - A list of examples for the natives provided by the plugin.
