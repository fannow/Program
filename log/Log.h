#ifndef __LOG_H__
#define __LOG_H_
#include<iostream>
#include<memory>
#include<memory.h>
#include<stdint.h>
#include<cstdarg>
#include<map>
using namespace std;

/*
* 用于控制台输出宏
*/
#define LOG_LEVEL(logger,level) \
    if(logger->GetLevel() <= level) \
			LogEventWarp(LogEvent::ptr(new LogEvent(logger, level,__FILE__,\
			__LINE__, 0, 1,2, time(0)))).getSS()
#define LOG_DEBUG(logger) LOG_LEVEL(logger, LogLevel::DEBUG)
#define LOG_ERROR(logger) LOG_LEVEL(logger, LogLevel::ERROR)
#define LOG_FATAL(logger) LOG_LEVEL(logger, LogLevel::FATAL)
#define LOG_INFO(logger) LOG_LEVEL(logger, LogLevel::INFO)
#define LOG_WARN(logger) LOG_LEVEL(logger, LogLevel::WARN)

#define LOG_ROOT()  LogRoot::GetInstance()->getroot()

class Logger;
class LogLevel{
    public:
        typedef shared_ptr<LogLevel>ptr;
        enum Level{
            UNKNOW,
            DEBUG,
            INFO,
            WARN,
            ERROR,
            FATAL,
        };
  static  string ToString(LogLevel::Level level);
  static LogLevel::Level FormString(string str);
};
#include<sstream>
class LogEvent{
    private:
        const char*file_name;           //日志器名称
        uint32_t line;                  //行好
        uint32_t m_time;                //程序运行时间
        uint32_t threadid;              //线程id、
        uint32_t fiberid;               //协程id
        uint32_t t_time;                //事件戳
        shared_ptr<Logger> logger;
		stringstream sss;
        LogLevel::Level level;
    public:
        typedef shared_ptr<LogEvent>ptr;
        LogEvent(shared_ptr<Logger> logger,LogLevel::Level level,const char* name,uint32_t line,uint32_t m_time,uint32_t threadid,uint32_t fiberid,uint32_t t_time);
        const char*GetName(){return file_name;}
        uint32_t GetLine(){return line;}
        uint32_t GetTime(){return m_time;}
        uint32_t GetThreadId(){return threadid;}
        uint32_t GetFiberId(){return fiberid;}
        shared_ptr<Logger> GetLogger(){return logger;}
        LogLevel::Level GetLevel(){return level;}
        uint32_t GetNowTime(){return t_time;}
        void format(const char*fmt,...);
        void format(const char*fmt,va_list va);
        stringstream&getss(){return sss;}
};
#include<list>
#include<vector>
class Formater{
    public:
        Formater(string str):
            formate(str)
    {
        cout<<str<<endl;
        Init();//构造对象时直接将日志格式个日志格式单元对应起来
    }
       typedef shared_ptr<Formater> ptr;
       class Item{
           public:
               typedef shared_ptr<Item>ptr;
            virtual  void  format(ostream &os ,shared_ptr<Logger> logger,LogLevel::Level level ,LogEvent::ptr event)=0;
              ~Item(){}
       };
        string format(shared_ptr<Logger> Logger ,LogLevel::Level level ,LogEvent::ptr event);//循环调用日志控制单元将格式化的数据一字符传形式连接在一起
        void Init();//解析日志格式 将对应的日志格式和日志格式控制单元对应起来
        string GetFormate(){return formate;}
		bool IsError(){return isno;} //检测日志格式是不是有错误
       private:
		bool isno;
        string formate;//用户输入的日志
        vector<Item::ptr> m_items;
};
class LogAppender{
    public:
        typedef  shared_ptr<LogAppender>ptr;
        virtual void log(shared_ptr<Logger>logger,LogLevel::Level level,LogEvent::ptr event)=0;
		//设置日志输出器自己的日志格式
        void SetFormate(Formater::ptr formate){
			this->formate=formate;
			if(formate){
              has=true;
            }else{
                has=false;
            }

		}
        LogLevel::Level GetLevel(){return level;}
        string GetFormate(){return  formate->GetFormate();}
    protected:

		bool has;
        Formater::ptr formate;
        LogLevel::Level level;
};
#include<fstream>
class FileAppender:public LogAppender{
    public:
        typedef shared_ptr<FileAppender>ptr;
        FileAppender(const char*fileA):
            file_name(fileA){
                reopen();
                
            }
     void log(shared_ptr<Logger>logger,LogLevel::Level level,LogEvent::ptr event);
     bool reopen();//打开日志文件
    private:
     const char*file_name;
     ofstream file_stream;
};
#include<sstream>
#include<vector>
class StdoutAppender:public LogAppender{
    public:
         typedef shared_ptr<StdoutAppender> ptr;
        
         void log(shared_ptr<Logger>logger,LogLevel::Level level,LogEvent::ptr event);
};
class Logger:public enable_shared_from_this<Logger>{
    public:
        Logger(string name="root"){
           this->name=name;
            //设置默认日志格式
            formate.reset(new Formater("%d%T%t%T%F%T[%p]%T[%c]%T%f:%l%T%m %n"));
        }
        typedef shared_ptr<Logger>ptr;
        void AddAppender(LogAppender::ptr app);
        void delAppedner(LogAppender::ptr app);
        void CleanAppender(){appenders.clear();}
        string GetLoggerName(){return name;}
        void SetFormat(Formater::ptr formate);
        void SetStringFormat(string str);
        void SetLogger(Logger::ptr logger){root=logger;}
        string GetFormate(){return formate->GetFormate();}
        void SetLevel(LogLevel::Level level){this->level=level;}
        void log(LogLevel::Level level,LogEvent::ptr event);
        LogLevel::Level GetLevel(){return level;}
    private:
        string name;
        Logger::ptr root;
        Formater::ptr formate;
        LogLevel::Level level;
        list<LogAppender::ptr> appenders;
};
#include<unordered_map>
class LoggerMes{
    public:
        typedef shared_ptr<LoggerMes> ptr;
        LoggerMes(){
            //构造默认日志器并加入到日志器队列中
            root.reset(new Logger());
            //添加默认日志输出器
            root->AddAppender(LogAppender::ptr(new StdoutAppender()));
            mp[root->GetLoggerName()] =root;
        }
        Logger::ptr getlogger(string name){
             auto it = mp.find(name);
             if(it!=mp.end()){
	        	return it->second;
        	}
             //不存在创建一个logger
            Logger::ptr logger(new Logger(name));
             logger->SetLogger(root);
             mp[name]=logger;
            return logger;
        }
        Logger::ptr getroot(){return root;}
    private:
        Logger::ptr root;
        unordered_map<string,Logger::ptr> mp;
};
/*
*
* LogEventWarp作为一个零时对象，在使用完后直接析构，触发日志直接写入，
*然而日志本身是智能指针，如果在声明在主函数里面，程序不结束将无法释放
*/
class LogEventWarp {
public:

	LogEventWarp(LogEvent::ptr e)
		:m_event(e) {}
	~LogEventWarp() {
		m_event->GetLogger()->log(m_event->GetLevel(), m_event);
	}
	shared_ptr<LogEvent>	getevent() { return m_event; }
	//获取日志内容流
	stringstream& getSS() { return m_event->getss(); }
private:
	//日志事件
	shared_ptr<LogEvent> m_event;


};
template<class T,class K=void>
class Signal{
    public:
        static T* GetInstance() {

		static T v;
		return &v;
	}
};
typedef Signal<LoggerMes> LogRoot;
#endif
