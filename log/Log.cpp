#include"Log.h"
/*
 *实现日志器事件
 * 
 * */
LogLevel::Level LogLevel::FormString(string str){
#define XX(level,v)\
    if(str==#v){\
      return LogLevel::level;\
    }

    XX(DEBUG,debug);
    XX(INFO,info);
    XX(WARN,warn);
    XX(ERROR,error);
    XX(FATAL,fatal);
    XX(DEBUG,DEBUG);
    XX(INFO,INFO);
    XX(WARN,WARN);
    XX(ERROR,ERROR);
    XX(FATAL,FATAL);
      return LogLevel::UNKNOW;
#undef XX
}
string LogLevel::ToString(LogLevel::Level level){
    switch (level) {
#define XX(name)\
	case name:\
	return #name;\

		XX(DEBUG);
		XX(WARN);
		XX(INFO);
		XX(ERROR);
		XX(FATAL);
#undef XX
	default:
		return "UNKNOW";
	}
	return "UNKNOW";
}


/*
 *
 * 日志事件实现
 * */
LogEvent::LogEvent(shared_ptr<Logger>logger,LogLevel::Level level,const char* name,uint32_t line,uint32_t m_time,uint32_t threadid,uint32_t fiberid,uint32_t t_time):
    file_name(name),line(line),m_time(m_time),threadid(threadid),fiberid(fiberid),
    t_time(t_time),logger(logger),level(level){}
void LogEvent::format(const char* fmt,...){
	 va_list al;
	va_start(al, fmt);
	format(fmt, al);
	va_end(al);      
}
void LogEvent::format(const char* fmt,va_list al){
	char* buff = NULL;
        int len = vasprintf(&buff, fmt, al);

        if (len != -1) {
                    sss << string(buff, len);
                        
        }
            delete buff;
}

/*
日志控制单元实现
**/

//消息控制单元

class Messageitemforma :public Formater::Item {
public:
	typedef shared_ptr<Messageitemforma> ptr;
	Messageitemforma(string str = "") {}

	void format(ostream& os, shared_ptr<Logger> logger, LogLevel::Level leve, LogEvent::ptr event) override {
		os << event->getss();
	}

};
//日志级别控制单元
class Levelitemforma :public Formater::Item {
public:
	typedef shared_ptr<Messageitemforma> ptr;
	Levelitemforma(string str = "") {}

	void format(ostream& os, shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override {
		os << LogLevel::ToString(level);
	}

};
//程序启动后消耗时间
class Pleaseitemforma :public Formater::Item {
public:
	typedef shared_ptr<Messageitemforma> ptr;
	Pleaseitemforma(string str = "") {}
	void format(ostream& os, shared_ptr<Logger> logger, LogLevel::Level leve, LogEvent::ptr event) override {
		os << event->GetTime();
	}

};
//日志器名称
class lognameitemforma :public Formater::Item {
public:
	typedef shared_ptr<Messageitemforma> ptr;
	lognameitemforma(string str = "") {}
	void format(ostream& os, shared_ptr<Logger> logger, LogLevel::Level leve, LogEvent::ptr event) override {
		os << event->GetLogger()->GetLoggerName();
	}
};


//线程id
class ThreadIditemforma :public Formater::Item {
public:
	typedef shared_ptr<Messageitemforma> ptr;
	ThreadIditemforma(string str = "") {}
	void format(ostream& os, shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override {
		os << event->GetThreadId();
	}
};
//协程id
class fiberiditemforma :public Formater::Item {
public:
	typedef shared_ptr<Messageitemforma> ptr;
	fiberiditemforma(string str = "") {}
	void format(ostream& os, shared_ptr<Logger> logger, LogLevel::Level leve, LogEvent::ptr event) override {
		os << event->GetFiberId();
	}
};

//运行时间
class Timeitemforma :public Formater::Item {
private:
	//时间格式
	string time_formate;
public:
	typedef shared_ptr<Messageitemforma> ptr;
	Timeitemforma(string format = "%Y:%m:%d %H:%M:%S") :
		time_formate(format) {
		if (time_formate.empty()) {
			time_formate = "%Y:%m:%d %H:%M:%S";
		}
	}


	void format(ostream& os, shared_ptr<Logger> logger, LogLevel::Level leve, LogEvent::ptr event) override {
		//日志时间格式设置
		struct tm* tm;
		time_t t = event->GetNowTime();
		tm = localtime(&t);
		char buff[64];
        //时间格式设置函数
		strftime(buff, sizeof(buff), time_formate.c_str(), tm);
		os << buff;
	}

};

//文件名称
class filenameitemforma :public Formater::Item {
public:
	typedef shared_ptr<Messageitemforma> ptr;
	filenameitemforma(string str = "") {}
	void format(ostream& os, shared_ptr<Logger> logger, LogLevel::Level leve, LogEvent::ptr event) override {
		os << event->GetLine();
	}
};
//文件行号
class lineitemforma :public Formater::Item {
public:
	typedef shared_ptr<Messageitemforma> ptr;
	lineitemforma(string str = "") {}
	void format(ostream& os, shared_ptr<Logger> logger, LogLevel::Level leve, LogEvent::ptr event) override {
		os << event->GetLine();
	}
};


class stringitemforma :public Formater::Item {
public:
	typedef shared_ptr<Messageitemforma> ptr;
	stringitemforma(string format) :
		str(format) {}
	void format(ostream& os, shared_ptr<Logger> logger, LogLevel::Level leve, LogEvent::ptr event) override {
		os << str;
	}
private:

	string str;
};
class tabitemforma :public Formater::Item {
public:
	typedef shared_ptr<Messageitemforma> ptr;
	tabitemforma(string format) {}
	void format(ostream& os, shared_ptr<Logger> logger, LogLevel::Level leve, LogEvent::ptr event) override {
		os << '\t';
	}
};


class newlineitemforma :public Formater::Item {
public:
	typedef shared_ptr<Messageitemforma> ptr;
	newlineitemforma(string format) 
		 {}
	void format(ostream& os, shared_ptr<Logger> logger, LogLevel::Level leve, LogEvent::ptr event) override {
		os << endl;
	}
};
/*
日志格式控制实现

*/string Formater::format(shared_ptr<Logger> logger ,LogLevel::Level level,LogEvent::ptr evnt){
	stringstream  ss;
    int i=0;
    for(int i=0;i<m_items.size();i++){
        cout<<"i"<<endl;
	//调用日志格式控制单元的formdar将数据写进ss 返回给日志输出器用于日志的输出
		m_items[i]->format(ss,logger,level,evnt);
    }
	return ss.str();
}
//将日志格式和日志格式控制单元对应起来插入到vector中
void Formater::Init(){
//tuple(str,fmt,type)
	vector<tuple<string, string, int>>vec;

	string nstr;
	for (size_t i = 0;i < formate.size();i++) {
		if (formate[i] != '%') {
			nstr.append(1, formate[i]);
			continue;
		}
		//其实还是一个%
		if ((i + 1) < formate.size()) {
			if (formate[i + 1] == '%') {
				nstr.append(1, '%');
				continue;
			}
		}
		size_t n = i + 1;
		int fmt_staus = 0;
		int fmt_beign = 0;


		string str;
		string fmt;
		while (n < formate.size()) {
			//遇见空格
			if (!isalpha(formate[n]) && formate[n] != '}' && formate[n] != '{') {
				str = formate.substr(i + 1, n - i - 1);
				break;
			}
			if (fmt_staus == 0) {
				if (formate[n] == '{') {
					//字符串分割
					str = formate.substr(i + 1, n - i - 1);
					fmt_staus = 1;
					fmt_beign = n;
					n++;
					continue;
				}

			}
			else if (fmt_staus == 1) {
				if (formate[n] == '}') {
					//字符串分割
					fmt = formate.substr(fmt_beign + 1, n - fmt_beign - 1);
					//	cout << "#" << fmt << endl;
					fmt_staus = 0;
					++n;
					break;
				}

			}
			++n;
			if (n == formate.size()) {
				if (str.empty()) {
					str = formate.substr(i - 1);
				}
			}
		}

		if (fmt_staus == 0) {
			if (!nstr.empty()) {
				vec.push_back(make_tuple(nstr, string(), 0));
				nstr.clear();
			}
			str = formate.substr(i + 1, n - i - 1);

			//解析日志将日志存储在数组中

			vec.push_back(make_tuple(str, fmt, 1));
			i = n - 1;
		}
		else if (fmt_staus == 1) {
      isno=true;
			cout << "pattern parse error" << formate << "-" << formate.substr(i) << endl;
			//格式错误
			vec.push_back(make_tuple("<<pattern_error>>", fmt, 0));
		}
	}
	if (!nstr.empty()) {
		vec.push_back(make_tuple(nstr, "", 0));

	}

	/*
	* %m--->消息体
	* %p--->日志级别
	* %r--->启动的时间
	* %c--->日志名称
	* %t--->线程id
	* %n--->回车
	* %d--->时间
	* %f--->文件名
	* %l--->行号
	*/

	//function<Item::ptr(string str)> 返回值为iter::ptr 参数为string得函数
	static map<string, function<Formater::Item::ptr(string str)>> formar_item = {

#define xx(str,c) \
		{ #str,[](string fmt) {return Formater::Item::ptr(new c(fmt));}}

		xx(m, Messageitemforma),
		xx(p, Levelitemforma),
		xx(r, Pleaseitemforma),
		xx(c, lognameitemforma),
		xx(t, ThreadIditemforma),
		xx(n, newlineitemforma),
		xx(d, Timeitemforma),
		xx(f, filenameitemforma),
		xx(l, lineitemforma),
		xx(T, tabitemforma),
		xx(F, fiberiditemforma),

#undef xx

	};
	for (auto& i : vec) {
		if (get<2>(i) == 0) {
			m_items.push_back(Formater::Item::ptr(new stringitemforma(get<0>(i))));
		}
		else {
			auto it = formar_item.find(get<0>(i));
			if (it == formar_item.end()) {
        isno=true;
				m_items.push_back(Formater::Item::ptr(new stringitemforma("<<error_format %" + get<0>(i) + ">>")));
			}
			else {
				m_items.push_back(it->second(get<1>(i)));

			}

		}

	}

}
/*
 *文件输出器实现
 *
 * */
void FileAppender::log(shared_ptr<Logger> logger,LogLevel::Level le,LogEvent::ptr event){
    //将数据写进日志文件
    //先测试文件是不是打开
    //要不是打开状态 重新打开文件
   // 将数写进日志文件
   if(le>=level){
      file_stream<<formate->format(logger,le,event);
   }
    
}

bool FileAppender::reopen(){
    if(!file_stream){
        //先关闭文件再重新打开
        file_stream.close();
    }       
        file_stream.open(file_name);
    return !!file_stream;
}
void StdoutAppender::log(shared_ptr<Logger>logger,LogLevel::Level le,LogEvent::ptr event){
    if(le>=level){
        cout<<formate->format(logger,le,event);
    }
    
}
void Logger::AddAppender(LogAppender::ptr app){
    appenders.push_back(app);
}
void Logger::delAppedner(LogAppender::ptr app){
    for(auto it=appenders.begin();it!=appenders.end();++it) {
        if(*it==app){
            appenders.erase(it);
            break;
        }
    }
}

void Logger::log(LogLevel::Level level,LogEvent::ptr event){
    if(level>=this->level){
     if(!appenders.empty()){
         for(auto &o:appenders){
             //将自己作为参数传递过去
             auto self=shared_from_this();
            o->log(self,level,event);//调用日志器所属的输出器，将数据输出到对应的位置
         }
     }else{
         root->log(level,event);
     }   
    }
}
void Logger::SetFormat(Formater::ptr formate){
    formate=formate;
    for(auto &o:appenders){
        o->SetFormate(formate);
    }
}
void Logger::SetStringFormat(string str){
      Formater::ptr new_val(new Formater(str));
    if(new_val->IsError()){
      cout<<"Logger SetFormater name="<<name<<
        "value="<<formate<<"invalid formater"<<endl;;
      return;
    }
        SetFormat(new_val);
}
int main(){
    LOG_INFO(LOG_ROOT())<<"********";
}
