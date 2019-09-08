#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <iostream>


template <typename T>
class IBasicStream;

namespace
{
constexpr int kClassVersion = 1;
}

/*
    ToSerial and FromSerial are for backward support
    */

struct Calendar
{

  int day;
  int month;
  int year;

  Calendar() : day(0), month(0), year(0)
  {
  }

  Calendar &operator=(const Calendar &other)
  {
    day = other.day;
    month = other.month;
    year = other.year;
    return *this;
  }

  template <typename streamType>
  void ToSerial(IBasicStream<streamType> &stream)
  {
    stream << kClassVersion;
    stream << day;
    stream << month;
    stream << year;
  }

  //class version Going to use for future change;
  template <typename streamType>
  void FromSerial(IBasicStream<streamType> &stream)
  {
    int classVersion = 0;
    stream >> classVersion;
    stream >> day;
    stream >> month;
    stream >> year;
  }

  template <typename streamType>
  friend IBasicStream<streamType> &operator<<(IBasicStream<streamType> &stream, Calendar &Calendar)
  {
    Calendar.ToSerial(stream);
    return stream;
  }

  template <typename streamType>
  friend IBasicStream<streamType> &operator>>(IBasicStream<streamType> &stream, Calendar &Calendar)
  {
    Calendar.FromSerial(stream);
    return stream;
  }
};

struct Timings
{

  Calendar startDate;
  int numberOfDays;
  int duration;

  std::vector<Calendar> customDate;

  Timings() : startDate{}, numberOfDays(0), duration(0)
  {
  }

  Timings &operator=(const Timings &other)
  {
    startDate = other.startDate;
    numberOfDays = other.numberOfDays;
    duration = other.duration;
    customDate = other.customDate;
    return *this;
  }

  template <typename streamType>
  void ToSerial(IBasicStream<streamType> &stream)
  {
    stream << kClassVersion;
    stream << startDate;
    stream << numberOfDays;
    stream << duration;
    int size = int(customDate.size());
    stream << size;
    for (auto item : customDate)
    {
      stream << item;
    }
  }

  template <typename streamType>
  void FromSerial(IBasicStream<streamType> &stream)
  {
    int size = -1;
    int classVersion = 0;
    stream >> classVersion;
    stream >> startDate;
    stream >> numberOfDays;
    stream >> duration;

    stream >> size;
    customDate.clear();
    for (int i = 0; i < size; i++)
    {
      Calendar item;
      stream >> item;
      customDate.push_back(item);
    }
  }

  template <typename streamType>
  friend IBasicStream<streamType> &operator<<(IBasicStream<streamType> &stream, Timings &timings)
  {
    timings.ToSerial(stream);
    return stream;
  }

  template <typename streamType>
  friend IBasicStream<streamType> &operator>>(IBasicStream<streamType> &stream, Timings &timings)
  {
    timings.FromSerial(stream);
    return stream;
  }
};

// It should have title
// Reminder Title
// TODO: priority

struct Description
{

  std::string title;
  std::string reminderTitle;

  Description() : title(""), reminderTitle("")
  {
  }

  Description &operator=(const Description &other)
  {
    title = other.title;
    reminderTitle = other.reminderTitle;
    return *this;
  }

  template <typename streamType>
  void ToSerial(IBasicStream<streamType> &stream)
  {
    stream << kClassVersion;
    stream << title;
    stream << reminderTitle;
  }

  template <typename streamType>
  void FromSerial(IBasicStream<streamType> &stream)
  {
    int classVersion = 0;
    stream >> classVersion;
    stream >> title;
    stream >> reminderTitle;
  }

  template <typename streamType>
  friend IBasicStream<streamType> &operator<<(IBasicStream<streamType> &stream, Description &description)
  {
    description.ToSerial(stream);
    return stream;
  }

  template <typename streamType>
  friend IBasicStream<streamType> &operator>>(IBasicStream<streamType> &stream, Description &description)
  {
    description.FromSerial(stream);
    return stream;
  }
};

enum State
{
  Started,
  Ended,
  Suspended,
  InProgress,
  Invalid,
};

class SessionInfo
{

public:
  //ToDo : Way to make ctor private as only
  //so that Session Class can only access
  //but std::map is currently accessing It so not
  //possible write now.

  SessionInfo() noexcept : mDescription(), mTimings(), mState(State::Started)
  {
  }

  SessionInfo(const SessionInfo &other) : mDescription(other.mDescription),
                                          mTimings(other.mTimings),
                                          mState(other.mState)
  {
  }

  SessionInfo &operator=(const SessionInfo &other)
  {
    mDescription = other.mDescription;
    mTimings = other.mTimings;
    mState = other.mState;
    return *this;
  }

  SessionInfo(SessionInfo &&other) : mDescription(std::move(other.mDescription)),
                                     mTimings(std::move(other.mTimings)),
                                     mState(std::move(other.mState))
  {
  }

  SessionInfo &operator=(SessionInfo &&other)
  {
    mDescription = std::move(other.mDescription);
    mTimings = std::move(other.mTimings);
    mState = std::move(other.mState);
    return *this;
  }

  SessionInfo &SetTitle(const std::string &title)
  {
    mDescription.title = title;
    return *this;
  }

  ~SessionInfo()
  {
  }

  std::string GetTitle() const
  {
    return mDescription.title;
  }

  SessionInfo &SetState(const State &other)
  {
    mState = other;
    return *this;
  }

  State GetState()
  {
    return mState;
  }

  SessionInfo &SetReminderTitle(const std::string &reminderTitle)
  {
    mDescription.reminderTitle = reminderTitle;
    return *this;
  }

  std::string GetReminderTitle() const
  {
    return mDescription.reminderTitle;
  }

  SessionInfo &SetDescription(const Description &other)
  {
    mDescription.reminderTitle = other.reminderTitle;
    mDescription.title = other.title;
    return *this;
  }

  Description &GetDescription()
  {
    return mDescription;
  }

  template <typename streamType>
  void ToSerial(IBasicStream<streamType> &stream)
  {
    stream << kClassVersion;
    stream << mDescription;
    stream << mTimings;
    int state = mState;
    stream << state;
  }

  template <typename streamType>
  void FromSerial(IBasicStream<streamType> &stream)
  {
    int classVersion;
    stream >> classVersion;
    stream >> mDescription;
    stream >> mTimings;
    int state = 0;
    stream >> state;
    mState = (State)state;
  }

  template <typename streamType>
  friend IBasicStream<streamType> &operator>>(IBasicStream<streamType> &stream, SessionInfo &obj)
  {
    obj.FromSerial(stream);
    return stream;
  }

  template <typename streamType>
  friend IBasicStream<streamType> &operator<<(IBasicStream<streamType> &stream, SessionInfo &obj)
  {
    obj.ToSerial(stream);
    return stream;
  }

  SessionInfo &SetTimings(const Timings &other)
  {
    mTimings = other;
    return *this;
  }

private:
  //template<typename T> friend class ISessionDataBaseFactory;
  //friend class              Session;
  Description mDescription;
  Timings mTimings;
  State mState;
};

//This is the class which is responsible for storing session information with its interface.

template <typename childClass>

class ISessionDataBaseFactory
{
public:
  ISessionDataBaseFactory() noexcept
  {
  }

  template <typename streamType>

  bool LoadSession(IBasicStream<streamType> &stream)
  {
    auto childObj = static_cast<childClass *>(this);
    return childObj->LoadSessionImpl(stream);
  }

  void Clear() {
    auto childObj = static_cast<childClass *>(this);
    childObj->ClearImpl();
  }

  template <typename streamType>
  void SaveAllSession(IBasicStream<streamType> &stream)
  {
    auto childObj = static_cast<childClass *>(this);
    childObj->SaveAllSessionImpl(stream);
  }

  void SetSessionInfo(std::string &sessionId, SessionInfo &info)
  {
    auto childObj = static_cast<childClass *>(this);
    childObj->SetSessionInfoImpl(sessionId, info);
  }

  SessionInfo &GetSessionInfo(const std::string &sessionId)
  {
    auto childObj = static_cast<childClass *>(this);
    return childObj->GetSessionInfoImpl(sessionId);
  }
  /* will be making SessionInfo as private */
  SessionInfo &BuildSessionInfo()
  {
    auto childObj = static_cast<childClass *>(this);
    return childObj->BuildSessionInfoImpl();
  }
};

//

class Session : public ISessionDataBaseFactory<Session>
{

public:
  Session() noexcept : mSessionStore{}, invalidStateObj{}, session{}
  {
    invalidStateObj.SetState(State::Invalid);
    session.SetState(State::Started);
    mSessionStore.clear();
  }

  /*
      The members of the map are internally stored in a tree structure. 
      There is no way to build the tree until you know the keys and values 
      that are to be stored.
      */

  template <typename streamType>
  bool LoadSessionImpl(IBasicStream<streamType> &stream)
  {
    int size = -1;
    stream >> size;

    if (stream.IsValid() && size > 0)
    {
      for (int i = 0; i < size; i++)
      {
        std::string key;
        SessionInfo value;
        stream >> key;
        stream >> value;
        mSessionStore.insert(std::make_pair(key, value));
      }

      return true;
    }
    return false;
  }

  //TODO : in future invalid mState object is going to use more
  SessionInfo &ClearImpl() {
    mSessionStore.clear();
  }

  SessionInfo &GetSessionInfoImpl(const std::string &sessionId)
  {
    int size = mSessionStore.size();

    if (size > 0 && mSessionStore.find(sessionId) != mSessionStore.end())
    {
      return mSessionStore[sessionId];
    }
    else
    {
      return invalidStateObj;
    }
  }

  template <typename streamType>
  void SaveAllSessionImpl(IBasicStream<streamType> &stream)
  {

    if (mSessionStore.size() > 0)
    {
      int size = int(mSessionStore.size());
      stream << size;
      for (auto &item : mSessionStore)
      {
        stream << item.first;
        stream << item.second;
      }
      stream.Flush();
    }
  }

  //TODO: Add logic to genrate session ID's
  void SetSessionInfoImpl(std::string &sessionId, SessionInfo &info)
  {
    if (mSessionStore.size() > 0 && mSessionStore.find(sessionId) != mSessionStore.end())
    {
      mSessionStore[sessionId] = info;
    }
    else
    {
      mSessionStore.insert(std::make_pair(sessionId, info));
    }
  }

  SessionInfo &BuildSessionInfoImpl()
  {
    return session;
  }

  ~Session() noexcept
  {
  }

  //Timing Methods

private:
  std::map<std::string, SessionInfo> mSessionStore;
  SessionInfo invalidStateObj;
  SessionInfo session;
};

/*
        
    */

//These classes responsible for proving stream classes.

template <typename childClass>
class IBasicStream
{
public:
  IBasicStream() noexcept
  {
  }

  IBasicStream(const std::string filename) noexcept
  {
  }

  IBasicStream(IBasicStream<childClass> &&other)
  {
    //Nothing needed ...
  }

  ~IBasicStream()
  {
  }

  IBasicStream<childClass> &operator=(IBasicStream<childClass> &&other)
  {
    // Nothing n
  }

  void Open(const std::string &filePath)
  {
    auto child = static_cast<childClass *>(this);
    child->OpenImpl(filePath);
  }

  bool IsValid()
  {
    auto child = static_cast<childClass *>(this);
    return child->IsValidImpl();
  }

  /***Issue here is that 
          i need operator ">>" and "<<" for all
          the implicit types but i don't want 
          for class so can't make genric.
          may be need to create for double and other class Too
          
          other are using friend function to do that 
        ***/
  void operator<<(const int &data)
  {
    auto child = static_cast<childClass *>(this);
    child->ToSerial(data);
  }

  void operator<<(const char &data)
  {
    auto child = static_cast<childClass *>(this);
    child->ToSerial(data);
  }

  /* void operator<<(std::string & data) {
        auto child = static_cast< childClass * >(this);
        child->FromSerial(data);
      }*/

  void operator<<(const float &data)
  {
    auto child = static_cast<childClass *>(this);
    child->ToSerial(data);
  }

  void operator<<(const std::basic_string<char> &data)
  {
    auto child = static_cast<childClass *>(this);
    bool isEmpty = data.empty();
    child->ToSerial(isEmpty);
    std::string c11String(data);
    child->ToSerial(c11String);
  }

  void operator>>(std::basic_string<char> &data)
  {
    auto child = static_cast<childClass *>(this);
    bool isEmpty = true;
    child->FromSerial(isEmpty);
    if(!isEmpty) {
      std::string c11String = "";
      child->FromSerial(c11String);
      data = std::basic_string<char>(c11String);
    }
  }

  void operator>>(char &data)
  {
    auto child = static_cast<childClass *>(this);
    child->FromSerial(data);
  }

  /*void operator>>(std::string & data) {
        auto child = static_cast< childClass * >(this);
        child->FromSerial(data);
      }*/

  void operator>>(float &data)
  {
    auto child = static_cast<childClass *>(this);
    child->FromSerial(data);
  }

  void operator>>(int &data)
  {
    auto child = static_cast<childClass *>(this);
    child->FromSerial(data);
  }

  bool IsEmpty()
  {
    auto child = static_cast<childClass *>(this);
    return child->IsEmptyImpl();
  }

  void Clear()
  {
    auto child = static_cast<childClass *>(this);
    child->ClearImpl();
  }

  void Flush()
  {
    auto child = static_cast<childClass *>(this);
    child->FlushImpl();
  }
};

class BinaryStream : public IBasicStream<BinaryStream>
{
public:
  BinaryStream() : Parent()
  {
   
  }
  
  ~BinaryStream() {
     mBinaryStream.close();
  }

  BinaryStream(const std::string filename) noexcept
  {
    //For creating ...
    mBinaryStream.open(filename,std::fstream::out);
    
    if(mBinaryStream.is_open()) {
      mBinaryStream.close();
      mBinaryStream.open(filename,std::fstream::out | std::fstream::in | std::fstream::binary);
    }
  
  }

  void OpenImpl(const std::string filename)
  {
    if (!IsValidImpl())
    {
      mBinaryStream.open(filename, std::fstream::in | std::fstream::out | std::fstream::trunc);
    }
  }

  BinaryStream(BinaryStream &&other) : Parent(std::move(other))
  {
    *this = std::move(other);
  }

  BinaryStream &operator=(BinaryStream &&other)
  {
    mBinaryStream = std::move(other.mBinaryStream);
    return *this;
  }

  template <typename T>
  void ToSerial(T &data)
  {
    if (mBinaryStream.is_open())
    {
      mBinaryStream << data;
    }
  }

  template <typename T>
  void FromSerial(T &data)
  {
    if (mBinaryStream.is_open())
    {
      if(mBinaryStream.peek() == std::fstream::traits_type::eof()) {
        mBinaryStream.seekg(0);
      }
      mBinaryStream >> data;
    }
  }

  bool IsValidImpl()
  {
    return mBinaryStream.is_open();
  }

  bool IsEmptyImpl()
  {
    return mBinaryStream.peek() == std::fstream::traits_type::eof();
  }

  void ClearImpl()
  {
    if (mBinaryStream.is_open())
    {
      mBinaryStream.clear();
    }
  }

  void FlushImpl()
  {
    if (mBinaryStream.is_open())
    {
      mBinaryStream << std::flush;
      mBinaryStream.flush();
      //mBinaryStream.sync();
    }
  }

  // friend std::fstream &operator<<(std::fstream &stream, std::string &str)
  // {
  //   int size = 0;
  //   size = str.size();
  //   stream.write(str.c_str(), size);
  //   return stream;
  // }

  // friend std::fstream &operator>>(std::fstream &stream, std::string &str)
  // {
  //   int length = 0;
  //   stream >> length;
  //   char cstr[length];
  //   stream.read(cstr, length);
  //   str = std::string(cstr);
  //   return stream;
  // }

private:
  typedef IBasicStream<BinaryStream> Parent;
  std::fstream mBinaryStream;
};

// Save Session Class

//Test case :

