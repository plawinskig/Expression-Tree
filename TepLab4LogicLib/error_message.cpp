#include "pch.h"
#include "error_message.hpp"

ErrorMessage::ErrorMessage(std::string message)
	:message_(message)
{
}

std::string ErrorMessage::get_message() const
{
	return message_;
}
