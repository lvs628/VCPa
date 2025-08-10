#if defined (_FSAPRCDLL)
    #define _FSAPRCCLASS Q_DECL_EXPORT
#elif defined (_FSAPRCAPP)
    #define _FSAPRCCLASS Q_DECL_IMPORT
#else
    #define _FSAPRCCLASS
#endif
