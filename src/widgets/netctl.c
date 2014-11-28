#include "widgets.h"
#include "netctl.h"

void*
widget_main (struct widget *widget) {
	struct widget_config config = widget_config_defaults;
	widget_init_config_string(widget->config, "script_file", config.script_file);
	widget_init_config_integer(widget->config, "refresh_interval", config.refresh_interval);

	widget_epoll_init(widget);
	while (true) {
		LOG_DEBUG("test");
		widget_epoll_wait_goto(widget, config.refresh_interval, cleanup);
	}

cleanup:

	widget_epoll_cleanup(widget);
	widget_clean_exit(widget);
}
