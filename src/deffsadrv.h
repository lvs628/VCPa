#if defined (_FSADRVDLL)
    #define _FSADRVCLASS Q_DECL_EXPORT
#elif defined (_FSADRVAPP)
    #define _FSADRVCLASS Q_DECL_IMPORT
#else
    #define _FSADRVCLASS
#endif
