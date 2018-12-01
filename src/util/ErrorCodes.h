namespace ErrorCodes {
    enum class FileError : int {
        NotFound = 01, CantOpen = 02
    };

    enum class LogicError : int {
        IncorrectDirection = 11, NodeNotFound = 12
    };


    template<class T>
    int i(T t) {
        return static_cast<int>(t);
    }

}
