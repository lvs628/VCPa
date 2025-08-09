#if defined (_FSAVARDLL)
    #define _FSAVARCLASS Q_DECL_EXPORT
#elif defined (_FSAVARAPP)
    #define _FSAVARCLASS Q_DECL_IMPORT
#else
	#define _FSAVARCLASS
#endif
