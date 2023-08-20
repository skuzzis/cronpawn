/**************************************
*  Natives Header File
***************************************/

#ifndef _natives_h

#define _natives_h

#include <string>
#include <amx/amx2.h>
#include <thread>
#include "../../src/common/common.hpp"
#include "../common/croncpp.h"
#include "../utilities/utilities.hpp"

namespace Natives {
	cell SetLogLevel(AMX* amx, cell* params);

	cell CreateCron(AMX* amx, cell* params);
	cell DeleteCron(AMX* amx, cell* params);
	cell SuspendCron(AMX* amx, cell* params);
	cell UnsuspendCron(AMX* amx, cell* params);
	cell DoesCronExists(AMX* amx, cell* params);
	cell ExecuteCron(AMX* amx, cell* params);

	void ExecuteCrons();
}

class Cron {
private:
	std::string cron_name, cron_settings, cron_args;
	Utilities::Callback* callback;
	cron::cronexpr cronexp;
	std::time_t executeTime;
	bool suspended = false;
public:
	Cron(std::string cron_name, std::string cron_settings, Utilities::Callback* callback, std::string cron_args, cron::cronexpr exp) {
		this->cron_name = cron_name;
		this->cron_settings = cron_settings;
		this->callback = callback;
		this->cron_args = cron_args;
		this->cronexp = exp;
		this->executeTime = cron::cron_next(this->cronexp, std::time(0));
	}

	std::string GetName() {
		return this->cron_name;
	}

	void SetSuspend(bool toggle) {
		this->suspended = toggle;
	}

	bool IsSuspended() {
		return this->suspended;
	}

	bool ShouldExecute(std::time_t time) {
		return this->executeTime == time;
	}

	void Execute() {
		this->executeTime = cron::cron_next(this->cronexp, std::time(0));
		this->callback->exec(this->cron_args.c_str());
		char debugMessage[128];
		snprintf(debugMessage, sizeof debugMessage, "CronJob \"%s\" with task \"%s\" has been executed.", this->cron_name.c_str(), this->cron_settings.c_str());
		Utilities::WriteDebugLog(debugMessage);
	}

	~Cron() {
		delete this->callback;
		this->suspended = false;
	}
};

#endif