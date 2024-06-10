/* ************************************************************************* */
/*      ##       ##      ## ##       ##      ## ##       ##      ##          */
/*       ##     ####    ##   ##     ####    ##   ##     ####    ##           */
/*        ##  ##   ##  ##     ##  ##   ##  ##     ##  ##   ##  ##            */
/*         ####     ####       ####     ####       ####     ####             */
/*          ##       ##         ##       ##         ##       ##              */
/*                                                                           */
/*           WONDERFUL            WEBSERV           WONDERTEAM               */
/*                                                                           */
/*      FELICIA KOOLHOVEN      FLEN HUISMAN       MARES VERBRUGGE            */
/*          fkoolhov             fhuisman             mverbrug               */
/*                                                                           */
/*          Codam Coding College        part of 42 network                   */
/*                            April - May 2024                               */
/* ************************************************************************* */

#ifndef CGI_HPP
# define CGI_HPP

# include "webserv.hpp"
# include "ASocket.hpp"

class Client;

class CGI : public ASocket
{
	private:
		Client&				_client;
		char**				_envp{};
		const std::string	_script_string{};
		const std::string	_extension;

	public:
		CGI(int read_end, Client& client);
		CGI(int write_end, Client& client, char** envp, std::string script_string);
		~CGI();

	Client&		getClient() const;
	char**		getEnvp() const;
	std::string	getScriptString() const;

	void	setEnvp(char** envp) = delete;

	void run_script();
	void readFromPipe();

};

#endif