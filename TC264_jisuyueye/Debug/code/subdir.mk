################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../code/Agorithm.c" \
"../code/Common_Peripherals.c" \
"../code/GPS.c" \
"../code/IMU.c" \
"../code/IMU_2.c" \
"../code/IMU_963.c" \
"../code/MahonyAHRS.c" \
"../code/images.c" 

COMPILED_SRCS += \
"code/Agorithm.src" \
"code/Common_Peripherals.src" \
"code/GPS.src" \
"code/IMU.src" \
"code/IMU_2.src" \
"code/IMU_963.src" \
"code/MahonyAHRS.src" \
"code/images.src" 

C_DEPS += \
"./code/Agorithm.d" \
"./code/Common_Peripherals.d" \
"./code/GPS.d" \
"./code/IMU.d" \
"./code/IMU_2.d" \
"./code/IMU_963.d" \
"./code/MahonyAHRS.d" \
"./code/images.d" 

OBJS += \
"code/Agorithm.o" \
"code/Common_Peripherals.o" \
"code/GPS.o" \
"code/IMU.o" \
"code/IMU_2.o" \
"code/IMU_963.o" \
"code/MahonyAHRS.o" \
"code/images.o" 


# Each subdirectory must supply rules for building sources it contributes
"code/Agorithm.src":"../code/Agorithm.c" "code/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fC:/Users/27322/AURIX-v1.10.6-workspace/TC264_offroad_Pro_by_Orrn/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/Agorithm.o":"code/Agorithm.src" "code/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/Common_Peripherals.src":"../code/Common_Peripherals.c" "code/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fC:/Users/27322/AURIX-v1.10.6-workspace/TC264_offroad_Pro_by_Orrn/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/Common_Peripherals.o":"code/Common_Peripherals.src" "code/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/GPS.src":"../code/GPS.c" "code/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fC:/Users/27322/AURIX-v1.10.6-workspace/TC264_offroad_Pro_by_Orrn/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/GPS.o":"code/GPS.src" "code/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/IMU.src":"../code/IMU.c" "code/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fC:/Users/27322/AURIX-v1.10.6-workspace/TC264_offroad_Pro_by_Orrn/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/IMU.o":"code/IMU.src" "code/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/IMU_2.src":"../code/IMU_2.c" "code/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fC:/Users/27322/AURIX-v1.10.6-workspace/TC264_offroad_Pro_by_Orrn/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/IMU_2.o":"code/IMU_2.src" "code/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/IMU_963.src":"../code/IMU_963.c" "code/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fC:/Users/27322/AURIX-v1.10.6-workspace/TC264_offroad_Pro_by_Orrn/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/IMU_963.o":"code/IMU_963.src" "code/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/MahonyAHRS.src":"../code/MahonyAHRS.c" "code/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fC:/Users/27322/AURIX-v1.10.6-workspace/TC264_offroad_Pro_by_Orrn/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/MahonyAHRS.o":"code/MahonyAHRS.src" "code/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/images.src":"../code/images.c" "code/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fC:/Users/27322/AURIX-v1.10.6-workspace/TC264_offroad_Pro_by_Orrn/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/images.o":"code/images.src" "code/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-code

clean-code:
	-$(RM) ./code/Agorithm.d ./code/Agorithm.o ./code/Agorithm.src ./code/Common_Peripherals.d ./code/Common_Peripherals.o ./code/Common_Peripherals.src ./code/GPS.d ./code/GPS.o ./code/GPS.src ./code/IMU.d ./code/IMU.o ./code/IMU.src ./code/IMU_2.d ./code/IMU_2.o ./code/IMU_2.src ./code/IMU_963.d ./code/IMU_963.o ./code/IMU_963.src ./code/MahonyAHRS.d ./code/MahonyAHRS.o ./code/MahonyAHRS.src ./code/images.d ./code/images.o ./code/images.src

.PHONY: clean-code

