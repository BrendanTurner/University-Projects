#pragma once
#include "json/json.h"

namespace Json {
	class customJsonWriter {
	public:
		customJsonWriter(std::string indentation = "\t");
		~customJsonWriter() {}

	public:
		/** \brief Serialize a Value in <a HREF="http://www.json.org">JSON</a> format.
		 * \param out Stream to write to. (Can be ostringstream, e.g.)
		 * \param root Value to serialize.
		 * \note There is no point in deriving from Writer, since write() should not
		 * return a value.
		 */
		void write(std::ostream& out, const Value& root);

	private:
		void writeValue(const Value& value);//customized
		void writeArrayValue(const Value& value);
		bool isMultineArray(const Value& value);
		void pushValue(const std::string& value);
		void writeIndent();
		void writeWithIndent(const std::string& value);
		void writeNoIndent(const std::string& value);//customized
		void indent();
		void unindent();
		void writeCommentBeforeValue(const Value& root);
		void writeCommentAfterValueOnSameLine(const Value& root);
		bool hasCommentForValue(const Value& value);
		static std::string normalizeEOL(const std::string& text);

		typedef std::vector<std::string> ChildValues;

		ChildValues childValues_;
		std::ostream* document_;
		std::string indentString_;
		int rightMargin_;
		std::string indentation_;
		bool addChildValues_;
	};
}