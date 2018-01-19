#ifndef SIMPLETRON_REDIRECTION_H
#define SIMPLETRON_REDIRECTION_H

struct cout_redirect {
	// From here: https://stackoverflow.com/a/5419388
	cout_redirect( std::streambuf * new_buffer )
			: old( std::cout.rdbuf( new_buffer ) )
	{ }

	~cout_redirect( ) {
		std::cout.rdbuf( old );
	}

private:
	std::streambuf * old;
};


#endif
