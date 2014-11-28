#include "widgets.h"
#include "netctl.h"

void*
widget_main (struct widget *widget) {
	struct widget_config config = widget_config_defaults;
	widget_init_config_string(widget->config, "script_file", config.script_file);
	widget_init_config_integer(widget->config, "refresh_interval", config.refresh_interval);

	widget_epoll_init(widget);
	while (true) {
		FILE *pipe = popen(config.script_file, "r");
		char buff[512];
		int len;

		if (!pipe) {
			LOG_DEBUG("pipe open failed");
			continue;
		}

		fgets(buff, sizeof(buff), pipe);
		len = strlen(buff);
		if (buff[len-1] == '\n') {
			buff[len-1] = 0;
		}

		LOG_DEBUG(buff);

		if (pclose(pipe) != 0) {
			LOG_DEBUG("pipe close failed");
		}

		widget_epoll_wait_goto(widget, config.refresh_interval, cleanup);
	}

cleanup:

	widget_epoll_cleanup(widget);
	widget_clean_exit(widget);
}
