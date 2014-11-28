static struct widget_config {
	const char *script_file;
	int refresh_interval;
} widget_config_defaults = {
	.script_file = "/home/aaron/netctl",
	.refresh_interval = 2,
};
