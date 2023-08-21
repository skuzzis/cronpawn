# Examples

There is a list of examples for Cronpawn.

## CreateCron

Creates a Cronjob using the cron expression provided.

Below is provided the cron expression you can use with this plugin:

```
<seconds> <minutes> <hours> <days of month> <months> <days of week> <years>
```

The following values are allowed for these fields:

| Field | Required | Allowed value | Allowed value (alternative 1) | Allowed value (alternative 2) | Allowed special characters |
| --- | --- | --- | --- | --- | --- |
| seconds | yes | 0-59 | 0-59 | 0-59 | `*` `,` `-` |
| minutes | yes | 0-59 | 0-59 | 0-59 | `*` `,` `-` |
| hours | yes | 0-23 | 0-23 | 0-23 | `*` `,` `-` |
| days of month | 1-31 | 1-31 | 1-31 | 1-31 | `*` `,` `-` `?` `L` `W` |
| months | yes | 1-12 | 0-11 | 1-12 | `*` `,` `-` |
| days of week | yes | 0-6 | 1-7 | 1-7 | `*` `,` `-` `?` `L` `#` |
| years | no | 1970-2099 | 1970-2099 | 1970-2099 | `*` `,` `-` |

Examples: 

| CRON | Description |
| --- | --- |
| * * * * * * | Every second |
| \*/5 * * * * ? | Every 5 seconds |
| 0 \*/5 \*/2 * * ? | Every 5 minutes, every 2 hours |
| 0 \*/2 \*/2 ? \*/2 */2 | Every 2 minutes, every 2 hours, every 2 days of the week, every 2 months |
| 0 15 10 * * ? * | 10:15 AM every day |
| 0 0/5 14 * * ? | Every 5 minutes starting at 2 PM and ending at 2:55 PM, every day |
| 0 10,44 14 ? 3 WED | 2:10 PM and at 2:44 PM every Wednesday of March |
| 0 15 10 ? * MON-FRI | 10:15 AM every Monday, Tuesday, Wednesday, Thursday and Friday |
| 0 15 10 L * ? | 10:15 AM on the last day of every month |
| 0 0 12 1/5 * ? | 12 PM every 5 days every month, starting on the first day of the month |
| 0 11 11 11 11 ? | Every November 11th at 11:11 AM |

```pawn
new CronID: cron;

public OnGameModeInit() {
	cron = CreateCron("test", "*/3 * * * * ?", "TestCron", "fiis", 13.37, 100, 200, "test");
	return 1;
}
```

## DeleteCron

Deletes the Cronjob from the server.

```pawn
new success = DeleteCron(cron);
```

## SuspendCron

Suspends the execution of Cronjob from the server.

```pawn
new success = SuspendCron(cron);
```

## UnsuspendCron

Unsuspends the execution of Cronjob from the server.

```pawn
new success = UnsuspendCron(cron);
```

## DoesCronExists

Checks if the cronjob exists on the server.

```pawn
new exists = DoesCronExists(cron);
```

## ExecuteCron

Executes the Cronjob if that moment. If the second argument is true, it executes the Cronjob even if it's suspended.

```pawn
new success = ExecuteCron(cron, true);
```

## cronpawn_SetLogLevel

Sets the log level of the plugin.

```pawn
public OnGameModeInit() {
	cronpawn_SetLogLevel(LOG_ERROR | LOG_WARNING | LOG_DEBUG); // logs everything
	cronpawn_SetLogLevel(LOG_ERROR | LOG_WARNING); // logs only error and warning messages
	cronpawn_SetLogLevel(LOG_ERROR | LOG_DEBUG); // logs only warning and debug messages
	cronpawn_SetLogLevel(LOG_WARNING | LOG_DEBUG); // logs only warning and debug messages
	cronpawn_SetLogLevel(LOG_ERROR); // logs only error messages
	cronpawn_SetLogLevel(LOG_WARNING); // logs only warning messages
	cronpawn_SetLogLevel(LOG_DEBUG); // logs only debug messages
}
```

## External Links

[Quick-Start](https://github.com/skuzzis/cronpawn/blob/master/pages/quick_start.md) - Quick-Start for Cronpawn.

[Natives](https://github.com/skuzzis/cronpawn/blob/master/pages/natives.md) - A list of natives provided by the plugin.
