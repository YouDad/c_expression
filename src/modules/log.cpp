#include <stdio.h>

#include "modules/log.h"

namespace log {
	int (* $_log)(const char *fmt, ...) = printf;
	int (* $_vlog)(const char *fmt, va_list va) = vprintf;
	int _level = 0;

	void set_level(enum LOG_LEVEL level) {
		if (LL_ERROR <= level && level <= LL_DEBUG) {
			_level = level;
		}
	}
	void debug(const char *fmt, ...) {
		if (_level >= 3) {
			$fg_rgb(0x666666);
			va_list ap;
			va_start(ap, fmt);
			$_vlog(fmt, ap);
			va_end(ap);
			$reset_color();
			$_log("\n");
		}
	}
	void info(const char *fmt, ...) {
		if (_level >= 2) {
			$fg_rgb(0x2288ff);
			va_list ap;
			va_start(ap, fmt);
			$_vlog(fmt, ap);
			va_end(ap);
			$reset_color();
			$_log("\n");
		}
	}
	void warn(const char *fmt, ...) {
		if (_level >= 1) {
			$fg_rgb(0xffaa44);
			va_list ap;
			va_start(ap, fmt);
			$_vlog(fmt, ap);
			va_end(ap);
			$reset_color();
			$_log("\n");
		}
	}
	void error(const char *fmt, ...) {
		if (_level >= 0) {
			$fg_rgb(0xffffff);
			$bg_rgb(0xff0000);
			va_list ap;
			va_start(ap, fmt);
			$_vlog(fmt, ap);
			va_end(ap);
			$reset_color();
			$_log("\n");
		}
	}
};
