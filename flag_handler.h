#ifndef FLAG__HANDLER
#define FLAG__HANDLER


class FlagHandler {

public:
	FlagHandler();

	enum class FlagType {
		zero,
		sign
	};

	bool get(FlagType flag_type);

	void set(FlagType flag_type, bool val);

private:
	bool flag_zero;
	bool flag_sign;

};


#endif /* FLAG__HANDLER */
