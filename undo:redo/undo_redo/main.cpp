#include <iostream>
#include <vector>

using namespace std;

// 指令
class Order {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Order() { }
};

// 指令集
class OrderSet : public Order {
private:
    std::vector<Order*> orders;
public:
    ~OrderSet(){
        for ( auto i : orders ) {
            delete i;
        }
    }
    // 向指令集中增加指令
    void add( Order* order ) {
        orders.push_back( order );
    }
    // 依次执行指令集中指令
    void execute() {
        for ( int i=0; i < orders.size(); i++ ) {
            orders[i]->execute();
        }
    }
    // undo指令集中指令
    void undo() {
        for ( int i=0; i < orders.size(); i++ ) {
            orders[i]->undo();
        }
    }
};

// 测试数据
class Test {
public:
    string text;
    
    void print() {
        cout << "I have " << text << "\n";
    }
};

// 历史记录
class Record {
private:
    std::vector<Order*> orders;
    int lastExecuted;
    int lastSaved;
public:
    Record() : lastExecuted(-1), lastSaved(-1) {}

    ~Record() {
        for ( auto i : orders ) {
            delete i;
        }
    }
    
    // add指令
    void add( Order* order) {
        // 删除LastExcuted之后的记录
        if ( lastExecuted + 1 < orders.size() ) {
            int count = (int)orders.size() - ( lastExecuted + 1 );
            int begin = lastExecuted + 1;
            int end = begin + count;
            
            for ( int i=0; i < count; i++ ) {
                delete orders[ begin + i ];
            }
            orders.erase( orders.begin() + begin, orders.begin() + end );
            lastSaved = -1;
        }
        
            order->execute();
        
        orders.push_back( order );
        lastExecuted = (int)orders.size() - 1;
    }

    // undo
    void undo() {
        if ( lastExecuted >= 0 ) {
            if ( orders.size() > 0 ) {
                orders[ lastExecuted ]->undo();
                lastExecuted--;
            }
        }
    }
    
    // redo
    void redo() {
        if ( lastExecuted + 1 < orders.size() ) {
            orders[ lastExecuted + 1 ]->execute();
            lastExecuted++;
        }
    }
};

class TestText : public Order {
protected:
    Test & command;
public:
    TestText( Test & command ) : command( command ) {}
};

class TestTextAdd : public TestText {
private:
    string str;
public:
    TestTextAdd( Test & command, string const & str ) : TestText(command), str(str) {
    }
    // 重写execute()
    void execute() {
        command.text += str;
    }
    // 重写undo()
    void undo() {
        auto len = command.text.length() - str.length();
        command.text.erase( len );
    }
};

int main() {
    Test command;
    command.text = "指令1";
    
    Record record;
    
    cout<<"--->初始指令! "<<endl;
    command.print();
    
    cout<<endl;cout<<endl;
    
    cout<<"--->Add一条指令!"<<endl;
    record.add( new TestTextAdd( command, "+指令2" ));
    command.print();
    record.add( new TestTextAdd( command, "+指令3" ));
    command.print();
    record.add( new TestTextAdd( command, "+指令4" ));
    command.print();
    
    cout<<"\n\n--->Undo上一条指令!\n"<<endl;
    record.undo();
    command.print();
    
    cout<<"\n\n--->Redo上一条指令!\n"<<endl;
    record.redo();
    command.print();
    
    cout<<"\n\n--->Undo上两条指令!\n"<<endl;
    record.undo();
    record.undo();
    command.print();
    
    cout<<"\n\n--->Add一条指令\n"<<endl;
    record.add( new TestTextAdd( command, "+指令5" ));
    command.print();
    
    // 此时Redo无效
    cout<<"\n\n--->Redo上一条指令! fail！！！\n"<<endl;
    record.redo();
    command.print();

    cout<<"\n\n--->Undo上一条指令!\n"<<endl;
    record.undo();
    command.print();

    cout<<"\n\n--->Undo上一条指令!\n"<<endl;
    record.undo();
    command.print();
    
    cout<<"\n\n--->Redo上一条指令!\n"<<endl;
    record.redo();
    command.print();
    
    cout<<"\n\n--->Redo上一条指令!\n"<<endl;
    record.redo();
    command.print();

    cout<<"\n--->Undo上一条指令!\n"<<endl;
    record.undo();
    command.print();
    
    cout<<endl<<endl;
    
}
