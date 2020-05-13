#
# Regular cron jobs for the gitid package
#
0 4	* * *	root	[ -x /usr/bin/gitid_maintenance ] && /usr/bin/gitid_maintenance
