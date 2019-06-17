#include "customJsonWriter.h"
#include <assert.h>

/*
customised the StyledStreamWriter from the Jsoncpp library by(Baptiste Lepilleur)

// //////////////////////////////////////////////////////////////////////
// Beginning of content of file: LICENSE
// //////////////////////////////////////////////////////////////////////

/*
The JsonCpp library's source code, including accompanying documentation,
tests and demonstration applications, are licensed under the following
conditions...

The author (Baptiste Lepilleur) explicitly disclaims copyright in all
jurisdictions which recognize such a disclaimer. In such jurisdictions,
this software is released into the Public Domain.

In jurisdictions which do not recognize Public Domain property (e.g. Germany as of
2010), this software is Copyright (c) 2007-2010 by Baptiste Lepilleur, and is
released under the terms of the MIT License (see below).

In jurisdictions which recognize Public Domain property, the user of this
software may choose to accept it either as 1) Public Domain, 2) under the
conditions of the MIT License (see below), or 3) under the terms of dual
Public Domain/MIT License conditions described here, as they choose.

The MIT License is about as close to Public Domain as a license can get, and is
described in clear, concise terms at:

http://en.wikipedia.org/wiki/MIT_License

The full text of the MIT License follows:

========================================================================
Copyright (c) 2007-2010 Baptiste Lepilleur

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use, copy,
modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
========================================================================
(END LICENSE TEXT)

The MIT license is compatible with both the GPL and commercial
software, affording one all of the rights of Public Domain with the
minor nuisance of being required to keep the above copyright notice
and license text in the source code. Note also that by accepting the
Public Domain "license" you can re-license your copy using whatever
license you like.

*/


// //////////////////////////////////////////////////////////////////////
// End of content of file: LICENSE
// //////////////////////////////////////////////////////////////////////

namespace Json{
	customJsonWriter::customJsonWriter(std::string indentation)
	: document_(NULL), rightMargin_(74), indentation_(indentation),
	addChildValues_() {}

void customJsonWriter::write(std::ostream& out, const Value& root) {
	document_ = &out;
	addChildValues_ = false;
	indentString_ = "";
	writeCommentBeforeValue(root);
	writeValue(root);
	writeCommentAfterValueOnSameLine(root);
	*document_ << "\n";
	document_ = NULL; // Forget the stream, for safety.
}

void customJsonWriter::writeValue(const Value& value) {
	switch (value.type()) {
	case nullValue:
		pushValue("null");
		break;
	case intValue:
		pushValue(valueToString(value.asLargestInt()));
		break;
	case uintValue:
		pushValue(valueToString(value.asLargestUInt()));
		break;
	case realValue:
		pushValue(valueToString(value.asDouble()));
		break;
	case stringValue:
		pushValue(valueToQuotedString(value.asCString()));
		break;
	case booleanValue:
		pushValue(valueToString(value.asBool()));
		break;
	case arrayValue:
		writeArrayValue(value);
		break;
	case objectValue: {
		Value::Members members(value.getMemberNames());
		if (members.empty())
			pushValue("{}");
		else {
			writeWithIndent("{");
			//indent();//changed no indent or new line
			Value::Members::iterator it = members.begin();
			for (;;) {
				const std::string& name = *it;
				const Value& childValue = value[name];
				writeCommentBeforeValue(childValue);
				writeNoIndent(valueToQuotedString(name.c_str()));//changed no indent or new line
				*document_ << " : ";
				writeValue(childValue);
				if (++it == members.end()) {
					writeCommentAfterValueOnSameLine(childValue);
					break;
				}
				*document_ << ",";
				writeCommentAfterValueOnSameLine(childValue);
			}
			//unindent();//changed no indent or new line
			writeNoIndent("}");//changed no indent or new line
		}
	} break;
	}
}

void customJsonWriter::writeArrayValue(const Value& value) {
	unsigned size = value.size();
	if (size == 0)
		pushValue("[]");
	else {
		bool isArrayMultiLine = isMultineArray(value);
		if (isArrayMultiLine) {
			writeWithIndent("[");
			indent();
			bool hasChildValue = !childValues_.empty();
			unsigned index = 0;
			for (;;) {
				const Value& childValue = value[index];
				writeCommentBeforeValue(childValue);
				if (hasChildValue)
					writeWithIndent(childValues_[index]);
				else {
					//writeIndent();//changed no indent or new line
					writeValue(childValue);
				}
				if (++index == size) {
					writeCommentAfterValueOnSameLine(childValue);
					break;
				}
				*document_ << ",";
				writeCommentAfterValueOnSameLine(childValue);
			}
			unindent();
			writeWithIndent("]");
		}
		else // output on a single line
		{
			assert(childValues_.size() == size);
			*document_ << "[ ";
			for (unsigned index = 0; index < size; ++index) {
				if (index > 0)
					*document_ << ", ";
				*document_ << childValues_[index];
			}
			*document_ << " ]";
		}
	}
}

bool customJsonWriter::isMultineArray(const Value& value) {
	int size = value.size();
	bool isMultiLine = size * 3 >= rightMargin_;
	childValues_.clear();
	for (int index = 0; index < size && !isMultiLine; ++index) {
		const Value& childValue = value[index];
		isMultiLine =
			isMultiLine || ((childValue.isArray() || childValue.isObject()) &&
				childValue.size() > 0);
	}
	if (!isMultiLine) // check if line length > max line length
	{
		childValues_.reserve(size);
		addChildValues_ = true;
		int lineLength = 4 + (size - 1) * 2; // '[ ' + ', '*n + ' ]'
		for (int index = 0; index < size; ++index) {
			writeValue(value[index]);
			lineLength += int(childValues_[index].length());
		}
		addChildValues_ = false;
		isMultiLine = isMultiLine || lineLength >= rightMargin_;
	}
	return isMultiLine;
}

void customJsonWriter::pushValue(const std::string& value) {
	if (addChildValues_)
		childValues_.push_back(value);
	else
		*document_ << value;
}

void customJsonWriter::writeIndent() {
	/*
	  Some comments in this method would have been nice. ;-)

	 if ( !document_.empty() )
	 {
		char last = document_[document_.length()-1];
		if ( last == ' ' )     // already indented
		   return;
		if ( last != '\n' )    // Comments may add new-line
		   *document_ << '\n';
	 }
	*/
	*document_ << '\n' << indentString_;
}

void customJsonWriter::writeWithIndent(const std::string& value) {
	writeIndent();
	*document_ << value;
}
//////////added here to write with no indent or new line
void customJsonWriter::writeNoIndent(const std::string & value)
{
	*document_ << value;
}
/////////////////////////////////////////////////////////

void customJsonWriter::indent() { indentString_ += indentation_; }

void customJsonWriter::unindent() {
	assert(indentString_.size() >= indentation_.size());
	indentString_.resize(indentString_.size() - indentation_.size());
}

void customJsonWriter::writeCommentBeforeValue(const Value& root) {
	if (!root.hasComment(commentBefore))
		return;
	*document_ << normalizeEOL(root.getComment(commentBefore));
	*document_ << "\n";
}

void customJsonWriter::writeCommentAfterValueOnSameLine(const Value& root) {
	if (root.hasComment(commentAfterOnSameLine))
		*document_ << " " + normalizeEOL(root.getComment(commentAfterOnSameLine));

	if (root.hasComment(commentAfter)) {
		*document_ << "\n";
		*document_ << normalizeEOL(root.getComment(commentAfter));
		*document_ << "\n";
	}
}

bool customJsonWriter::hasCommentForValue(const Value& value) {
	return value.hasComment(commentBefore) ||
		value.hasComment(commentAfterOnSameLine) ||
		value.hasComment(commentAfter);
}

std::string customJsonWriter::normalizeEOL(const std::string& text) {
	std::string normalized;
	normalized.reserve(text.length());
	const char* begin = text.c_str();
	const char* end = begin + text.length();
	const char* current = begin;
	while (current != end) {
		char c = *current++;
		if (c == '\r') // mac or dos EOL
		{
			if (*current == '\n') // convert dos EOL
				++current;
			normalized += '\n';
		}
		else // handle unix EOL & other char
			normalized += c;
	}
	return normalized;
}

}