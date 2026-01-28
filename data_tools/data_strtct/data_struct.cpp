#include "data_struct.h"

bool UserData::operator<(const UserData& other) const
{
    return this->id < other.id;
}

void UserData::log_info() const
{
    Logger::Info("UserData { id: " + std::to_string(id) + ", data: " + std::to_string(data) + " }");
}


std::ostream& operator<<(std::ostream& os, const UserData& u)
{
    os << "UserData { id: " << u.id << ", data: " << u.data << " }";
    return os;
}

