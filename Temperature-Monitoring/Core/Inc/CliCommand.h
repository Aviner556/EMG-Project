#ifndef CLICOMMAND_H_
#define CLICOMMAND_H_


class CliCommand
{
public:
	virtual ~CliCommand() {};

	virtual void doCommand(const char * param) = 0;
};

void CliCommand_init();

#endif /* CLICOMMAND_H_ */
