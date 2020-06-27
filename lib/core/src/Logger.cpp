#include <zeno/Core/Logger.hpp>
#include <iostream>

namespace ze {

	Logger::Logger() :
		Logger(Severity::Error) {
	}
	Logger::Logger(Severity _severity) :
		Logger(std::cout, _severity) {
	}
	Logger::Logger(std::ostream& _ostream) :
		Logger(_ostream, Severity::Error) {
	}
	Logger::Logger(std::ostream& _ostream, Severity _severity) :
		m_Severity(_severity),
		m_Ostream(_ostream) {

	}

}