/**************************************
*  Natives Source Code File
***************************************/

#include "natives.hpp"

uint32_t cronID = 0;
std::map<uint32_t, Cron*> crons;

// native CronID:CreateCron(const cron_name[], const cron_settings[], const callback[], const args[], {Float,_}:...);
cell Natives::CreateCron(AMX* amx, cell* params) {
	std::string cron_name = Utilities::GetString(amx, params, 1);
	std::string cron_settings = Utilities::GetString(amx, params, 2);
	std::string cron_callback = Utilities::GetString(amx, params, 3);
	std::string cron_args = Utilities::GetString(amx, params, 4);

	Utilities::Callback* callback = new Utilities::Callback(amx, cron_callback.c_str());
	callback->addFromFormat(amx, cron_args.c_str(), params, 4);
	bool created = false;

	try {
		cron::cronexpr created_cron = cron::make_cron<cron::cron_standard_traits>(cron_settings);
		Cron* crn = new Cron(cron_name, cron_settings, callback, cron_args, created_cron);
		++cronID;

		crons.insert(std::make_pair(cronID, crn));
		char debugMessage[256];
		snprintf(debugMessage, sizeof debugMessage, "CronJob %d (%s) with task \"%s\" has been created.", cronID, cron_name.c_str(), cron_settings.c_str());
		Utilities::WriteDebugLog(debugMessage);
		created = true;
	}
	catch (cron::bad_cronexpr const& ex) {
		char errorMessage[512];
		snprintf(errorMessage, sizeof errorMessage, "CronJob \"%s\" with task \"%s\" failed to create. Reason: %s", cron_name.c_str(), cron_settings.c_str(), (char*)ex.what());
		Utilities::WriteErrorLog(errorMessage);
		created = false;
	}

	return created;
}

// native DeleteCron(CronID:cronid);
cell Natives::DeleteCron(AMX* amx, cell* params) {
	uint32_t cronid = Utilities::GetInteger(amx, params, 1);
	if (crons.find(cronid) == crons.end()) {
		char message[64];
		snprintf(message, sizeof message, "CronJob %d doesn't exists.", cronid);
		Utilities::WriteWarningLog(message);
		return 0;
	}

	Cron* crn = crons[cronid];

	char message[128];
	snprintf(message, sizeof message, "CronJob %d (%s) has been deleted.", cronid, crn->GetName().c_str());
	Utilities::WriteDebugLog(message);

	delete crn;
	crons.erase(cronid);

	return 1;
}

// native SuspendCron(CronID:cronid);
cell Natives::SuspendCron(AMX* amx, cell* params) {
	uint32_t cronid = Utilities::GetInteger(amx, params, 1);
	if (crons.find(cronid) == crons.end()) {
		char message[64];
		snprintf(message, sizeof message, "CronJob %d doesn't exists.", cronid);
		Utilities::WriteWarningLog(message);
		return 0;
	}

	Cron* crn = crons[cronid];
	if (crn->IsSuspended()) {
		char message[128];
		snprintf(message, sizeof message, "CronJob %d (%s) has already been suspended.", cronid, crn->GetName().c_str());
		Utilities::WriteWarningLog(message);
		return 0;
	}

	char message[128];
	snprintf(message, sizeof message, "CronJob %d (%s) has been suspended.", cronid, crn->GetName().c_str());
	Utilities::WriteDebugLog(message);
	crn->SetSuspend(true);

	return 1;
}

// native UnsuspendCron(CronID:cronid);
cell Natives::UnsuspendCron(AMX* amx, cell* params) {
	uint32_t cronid = Utilities::GetInteger(amx, params, 1);
	if (crons.find(cronid) == crons.end()) {
		char message[64];
		snprintf(message, sizeof message, "CronJob %d doesn't exists.", cronid);
		Utilities::WriteWarningLog(message);
		return 0;
	}

	Cron* crn = crons[cronid];
	if (!crn->IsSuspended()) {
		char message[128];
		snprintf(message, sizeof message, "CronJob %d (%s) has already been unsuspended.", cronid, crn->GetName().c_str());
		Utilities::WriteWarningLog(message);
		return 0;
	}

	char message[128];
	snprintf(message, sizeof message, "CronJob %d (%s) has been unsuspended.", cronid, crn->GetName().c_str());
	Utilities::WriteDebugLog(message);
	crn->SetSuspend(false);

	return 1;
}

// native DoesCronExists(CronID:cronid);
cell Natives::DoesCronExists(AMX* amx, cell* params) {
	uint32_t cronid = Utilities::GetInteger(amx, params, 1);
	return crons.find(cronid) != crons.end();
}

// native ExecuteCron(CronID:cronid, bool:bypassSuspend = false);
cell Natives::ExecuteCron(AMX* amx, cell* params) {
	uint32_t cronid = Utilities::GetInteger(amx, params, 1);
	bool bypassSuspend = Utilities::GetInteger(amx, params, 2) != 0;

	if (crons.find(cronid) == crons.end()) {
		char message[64];
		snprintf(message, sizeof message, "CronJob %d doesn't exists.", cronid);
		Utilities::WriteWarningLog(message);
		return 0;
	}

	Cron* crn = crons[cronid];
	if (!bypassSuspend && crn->IsSuspended()) {
		char message[128];
		snprintf(message, sizeof message, "CronJob %d (%s) is suspended.", cronid, crn->GetName().c_str());
		Utilities::WriteWarningLog(message);
		return 0;
	}

	crn->Execute();

	return 1;
}

void Natives::ExecuteCrons() 
{
	while (true)
	{
		std::time_t now = std::time(0);
		for (auto const& ch : crons)
		{
			Cron* crn = ch.second;
			if (!crn->IsSuspended()) {
				if (crn->ShouldExecute(now)) crn->Execute();
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}

// TODO: Plugin Ticks for executing crons.

cell Natives::SetLogLevel(AMX* amx, cell* params) 
{
	Utilities::prepareLogging(Utilities::GetInteger(amx, params, 1));
	return 1;
}