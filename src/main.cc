#include "xserver/portal_service.h"
#include "shared/protocol.h"
#include "shared/logger.h"
#include "xserver/crash_handler.h"
#include <csignal>
#include <unistd.h>
#include <atomic>

static std::atomic<bool> g_running{true};

static void signal_handler(int) {
    g_running = false;
}

int main() {
    fbx::shared::Logger::init("xportal");
    fbx::xserver::installCrashHandler("xportal");
    LOG_INFO("xportal starting...");

    signal(SIGTERM, signal_handler);
    signal(SIGINT, signal_handler);

    LOG_INFO("PortalService running. Waiting for SIGTERM/SIGINT.");

    // PortalService is stateless (all methods are static); the IPC socket
    // is managed by the compositor. This daemon is a placeholder for
    // running PortalService as a standalone process in the future.
    while (g_running) {
        pause();
    }

    LOG_INFO("xportal shutting down.");
    return 0;
}
