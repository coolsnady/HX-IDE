#ifndef CHAINIDE_H
#define CHAINIDE_H

#include <QObject>
#include "DataDefine.h"

class ExeManager;
class CompileManager;
class QProcess;
class ChainIDE : public QObject
{
    Q_OBJECT
public:
//数据发送
    void postRPC(QString _rpcId, QString _rpcCmd);
//链类型
    int getCurrentChainType()const;
    void setCurrentChainType(int type);
//是否是沙盒
    bool isSandBoxMode()const;
    void setSandboxMode(bool mode);
//配置
    QString getEnvAppDataPath()const;
    QString getConfigAppDataPath()const;
    DataDefine::ThemeStyle getCurrentTheme()const;
    void setCurrentTheme(DataDefine::ThemeStyle)const;

    void setConfigAppDataPath(const QString &path);
//后台
    ExeManager *testManager()const;
    ExeManager *formalManager()const;
    QProcess *getProcess(int type = 0)const;//0当前 1测试  2正式
//编译
    CompileManager *getCompileManager()const;
public:
    void refreshStyleSheet();//刷新样式表
private:
    void getSystemEnvironmentPath();//系统环境变量寻找
    void InitConfig();//初始化配置
    void InitExeManager();//初始化后台
signals:
    void jsonDataUpdated(const QString &id,const QString &data);//接收到返回
    void rpcPosted(const QString & rpcId, const QString & rpcCmd);//测试链发出请求
    void rpcPostedFormal(const QString & rpcId, const QString & rpcCmd);//正式链发出请求
public:
    static ChainIDE *getInstance();
    ~ChainIDE();
private:
    explicit ChainIDE(QObject *parent = 0);
    static ChainIDE *_instance;
private:
    class DataPrivate;
    DataPrivate *_p;
};

#endif // CHAINIDE_H