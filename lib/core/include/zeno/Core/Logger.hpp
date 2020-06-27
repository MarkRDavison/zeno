#ifndef INCLUDED_ZENO_CORE_LOGGER_HPP_
#define INCLUDED_ZENO_CORE_LOGGER_HPP_

#include <ostream>
#include <string>

namespace ze {

	enum class Severity {
		Fatal = 4,
		Error = 3,
		Warning = 2,
		Info = 1,
		Trace = 0
	};

	class Logger {
	public:
		Logger();
		Logger(Severity _severity);
		Logger(std::ostream& _ostream);
		Logger(std::ostream& _ostream, Severity _severity);

		std::ostream& operator()() { return m_Ostream; }

		void log(Severity _severity, const std::string& _str) {
			if (_severity >= m_Severity) {
				log(_str);
			}
		}

		template<typename T, typename... Targs>
		void log(Severity _severity, const std::string& _format, const T& _value, const Targs&... _args) {
			if (_severity >= m_Severity) {
				log(_format, _value, _args...);
			}
		}

	private:
		void log(const std::string& _str) {
			m_Ostream << _str << std::endl;
		}

		template<typename T, typename... Targs>
		void log(const std::string& _format, const T& _value, const Targs&... _args) {
			for (unsigned i = 0; i < _format.size(); ++i) {
				const char fc = _format[i];
				if (fc == '%' && (i == 0 || _format[i] != '\\')) {
					m_Ostream << _value;
					log(_format.substr(i + 1), _args...);
					return;
				}
				m_Ostream << fc;
			}
		}

	private:
		Severity m_Severity;
		std::ostream& m_Ostream;
	};

}

#endif // INCLUDED_ZENO_CORE_LOGGER_HPP_