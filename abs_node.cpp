template <class T> class abs_node{
protected:
    T value;

    abs_node(T k){
        value = k;
    }

public:
    void set_value(T val){
        value = val;
    }

    T get_value(){
        return value;
    }
};