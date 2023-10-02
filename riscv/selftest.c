// SPDX-License-Identifier: GPL-2.0-only
/*
 * Test the framework itself. These tests confirm that setup works.
 *
 * Copyright (C) 2023, Ventana Micro Systems Inc., Andrew Jones <ajones@ventanamicro.com>
 */
#include <libcflat.h>
#include <cpumask.h>
#include <asm/processor.h>
#include <asm/setup.h>

static void check_cpus(void)
{
	int cpu;

	for_each_present_cpu(cpu)
		report_info("CPU%3d: hartid=%08lx", cpu, cpus[cpu].hartid);
}

static bool exceptions_work;

static void handler(struct pt_regs *regs)
{
	exceptions_work = true;
	regs->epc += 2;
}

static void check_exceptions(void)
{
	install_exception_handler(EXC_INST_ILLEGAL, handler);
	asm volatile(".4byte 0");
	install_exception_handler(EXC_INST_ILLEGAL, NULL);
	report(exceptions_work, "exceptions");
}

int main(int argc, char **argv)
{
	bool r;

	report_prefix_push("selftest");

	report(!strncmp(argv[0], "selftest", 8), "program name");

	if (argc > 1) {
		r = !strcmp(argv[1], "foo");
		if (argc > 2)
			r &= !strcmp(argv[2], "bar");
		if (argc > 3)
			r &= !strcmp(argv[3], "baz");
		report_info("matched %d command line parameters", argc - 1);
		report(r, "command line parsing");
	} else {
		report_skip("command line parsing");
	}

	if (getenv("FOO")) {
		r = !strcmp(getenv("FOO"), "foo");
		r &= !strcmp(getenv("BAR"), "bar");
		r &= !strcmp(getenv("BAZ"), "baz");
		report(r, "environ parsing");
	} else {
		report_skip("environ parsing");
	}

	check_exceptions();
	check_cpus();

	return report_summary();
}
