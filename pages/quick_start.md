# Quick-Start

## How I install the plugin?

To get started, you need to download the [Latest Release](https://github.com/skuzzis/cronpawn/releases) and put these two folders inside your server.

Next in your gamemode, you need to include the file like this:

```pawn
#include <a_samp>
#include <cronpawn>
...
```

## How to create a Cronjob?

Firstly you need to declare a variable with tag `CronID:` in your gamemode. and use `CreateCron()` at `OnGameModeInit()` to create it up.

```pawn

new CronID: cron;

public OnGameModeInit() {
    cron = CreateCron("every_second_cron", "* * * * * * ?", "CronCallback", "");
    return 1;
}

forward CronCallback();
public CronCallback() {
    print("Executed Cronjob");
}

```

## How do I use Cronpawn?

You can use it with the list of natives which are [here](https://github.com/skuzzis/cronpawn/blob/master/pages/natives.md).

Also, you can get some examples from [here](https://github.com/skuzzis/cronpawn/blob/master/pages/examples.md).

## External links

[Natives](https://github.com/skuzzis/cronpawn/blob/master/pages/natives.md) - A list of functions provided by the plugin.

[Examples](https://github.com/skuzzis/cronpawn/blob/master/pages/examples.md) - A list of natives for the natives provided by the plugin.
