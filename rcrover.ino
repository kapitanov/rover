#pragma region INCLUDES&usings

#include "rover_commanding_LightCommandInterpreter.h"
#include "rover_chassic_LightEmitter.h"
#include "rover_chassic.h"
#include "rover_telemetry.h"
#include "rover_commanding.h"
#include "rover_logic.h"

namespace telemetry = rover::telemetry;
namespace chassic = rover::chassic;
namespace commanding = rover::commanding;
namespace logic = rover::logic;

#pragma endregion

#pragma region TELEMETRY

telemetry::UartChannel uartChannel(9600);

#pragma endregion

#pragma region HARDWARE

chassic::MobilePlatform platform(chassic::MobilePlatformConfig(6, 7, 8, 9));

chassic::CameraMount cameraMount(2, 3);
chassic::RangingSensor rangingSensor(4, 5);
chassic::LightEmitter frontLight(22);

#pragma endregion

#pragma region LOGIC

logic::CollisionPrevention collisionPrevention(platform, rangingSensor);

#pragma endregion

#pragma region COMMANDING

commanding::CommandInterpreter* commandInterpreters[] = { NULL, NULL, NULL, NULL };
commanding::CompositeCommandInterpreter commandInterpreter(commandInterpreters, sizeof(commandInterpreters));
commanding::CommandReader commandReader(Serial, commandInterpreter);

commanding::ChassicCommandInterpreter chassicCmdInterpreter(platform);
commanding::CameraMountCommandInterpreter cameraMountCmdInterpreter(cameraMount);
commanding::SensorCommandInterpreter sensorCmdInterpreter(rangingSensor);
commanding::LightCommandInterpreter lightCmdInterpreter(frontLight);

#pragma endregion

#pragma region MAIN CODE

void setup()
{
	telemetry::initialize(uartChannel);

	telemetry::Logger::info("platform powered up");

	telemetry::Logger::info("setting up motors");
	platform.stop();

	telemetry::Logger::info("setting up camera mount");
	cameraMount.initialize();

	telemetry::Logger::info("setting up ranging sensor");
	rangingSensor.initialize();

	telemetry::Logger::info("setting up command interpreters");
	commandInterpreters[0] = &chassicCmdInterpreter;
	commandInterpreters[1] = &cameraMountCmdInterpreter;
	commandInterpreters[2] = &sensorCmdInterpreter;
	commandInterpreters[3] = &lightCmdInterpreter;
	
	telemetry::Logger::info("setting up internal logic");
	collisionPrevention.enable();

	telemetry::Logger::info("Sovereign is online");
}

void loop()
{
	commandReader.handleEvents();
	collisionPrevention.handleEvents();
}

#pragma endregion