
#include"../Conform/conform.h"
char* file_yaml = getcwd(NULL, 0);
/* 
 * 以yaml格式打印yaml文件中的数据
 *
 * */
void print(YAML::Node node,int level){
  if(node.IsScalar()){
    //yaml-------简单结构-----------直接输出
    LOG_INFO(LOG_ROOT())<<string(level*4,' ')<<node.Scalar()<<" - "<<node.Type()<<" - "<<level;
  }else if(node.IsNull()){

    LOG_INFO(LOG_ROOT())<<string(level*4,' ')<<"NULL - "<<node.Type()<<" - "<<level;
  }else if(node.IsMap()){
    //yaml------map类型-------------遍历
    for(auto it=node.begin();it!=node.end();it++){

     LOG_INFO(LOG_ROOT())<<string(level*4,' ')<<it->first<<" - " <<it->second.Type()<<" - "<<level;
     print(it->second,level+1);
    }
  }else if(node.IsSequence()){
    //yaml------线性结构-----------遍历
    for(size_t i=0;i<node.size();i++){

    LOG_INFO(LOG_ROOT())<<string(level*4,' ')<<i<<" - "<<node[i].Type()<<" - "<<level;
    print(node[i],level+1);
    }

  }

}
void func(){
    //加载yaml文件
    cout<<"加载文件"<<endl;
    string file="";
    file=file+file_yaml+"/text/config.yaml";
    LOG_INFO(LOG_ROOT())<<"helle";
    cout<<LogRoot::GetInstance()->toyamlstring()<<endl;
    cout<<"*****************************"<<endl;
    YAML::Node root=YAML::LoadFile(file.c_str());
    //解析yaml文件
    Config::LoadFormYaml(root);
    cout<<LogRoot::GetInstance()->toyamlstring()<<endl;;
    print(root,0);

}
int main(){
    func();
}
