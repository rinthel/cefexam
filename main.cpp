
#include <iostream>
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#include <include/cef_app.h>
#include <include/cef_browser.h>
#include <include/cef_command_line.h>
#include <include/cef_client.h>
#include <include/views/cef_browser_view.h>
#include <include/wrapper/cef_library_loader.h>

#pragma clang diagnostic pop

class Handler: public CefClient, public CefDisplayHandler, CefLifeSpanHandler, CefLoadHandler {
public:
    Handler() {}
    CefRefPtr<CefDisplayHandler> GetDisplayHandler() override { return this; }
    CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override { return this; }
    CefRefPtr<CefLoadHandler> GetLoadHandler() override { return this; }

    void OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title) override {
        
    }

    // CefLifeSpanHandler methods:
    void OnAfterCreated(CefRefPtr<CefBrowser> browser) override {

    }

    bool DoClose(CefRefPtr<CefBrowser> browser) override {
        return false;
    }

    void OnBeforeClose(CefRefPtr<CefBrowser> browser) override {

    }

    // CefLoadHandler methods:
    void OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode, const CefString& errorText, const CefString& failedUrl) override {

    }

private:
    IMPLEMENT_REFCOUNTING(Handler);

};

class App: public CefApp, public CefBrowserProcessHandler {
public:
    App() {}
    CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override { return this; }
    void OnContextInitialized() override {
        CefRefPtr<CefCommandLine> commandLine = CefCommandLine::GetGlobalCommandLine();

        #if defined(OS_WIN) || defined(OS_LINUX)
        // Create the browser using the Views framework if "--use-views" is specified
        // via the command-line. Otherwise, create the browser using the native
        // platform framework. The Views framework is currently only supported on
        // Windows and Linux.
        const bool use_views = commandLine->HasSwitch("use-views");
        #else
        const bool use_views = false;
        #endif

        // SimpleHandler implements browser-level callbacks.
        CefRefPtr<Handler> handler(new Handler());

        // Specify CEF browser settings here.
        CefBrowserSettings browser_settings;

        std::string url = "http://www.google.com";

        // if (use_views) {
        //     // Create the BrowserView.
        //     CefRefPtr<CefBrowserView> browser_view = CefBrowserView::CreateBrowserView(
        //         handler, url, browser_settings, nullptr, nullptr,
        //         new SimpleBrowserViewDelegate());

        //     // Create the Window. It will show itself after creation.
        //     CefWindow::CreateTopLevelWindow(new SimpleWindowDelegate(browser_view));
        // } else {
        //     // Information used when creating the native window.
            CefWindowInfo window_info;

        // #if defined(OS_WIN)
        //     // On Windows we need to specify certain flags that will be passed to
        //     // CreateWindowEx().
        //     window_info.SetAsPopup(NULL, "cefsimple");
        // #endif

            // Create the first browser window.
            if (!CefBrowserHost::CreateBrowser(window_info, handler, url, browser_settings, nullptr, nullptr)) {
                std::cout << "error?" << std::endl;
            }
        // }
    }
private:
    IMPLEMENT_REFCOUNTING(App);
};

int main(int argc, const char** argv) {
    CefScopedLibraryLoader library_loader;
    if (!library_loader.LoadInMain())
        return 1;

    CefRefPtr<CefApp> app(new App());
    CefMainArgs mainArgs(argc, (char**)argv);
    CefExecuteProcess(mainArgs, nullptr, NULL);

    CefSettings settings;
    CefInitialize(mainArgs, settings, nullptr, NULL);
    // settings.no_sandbox = true;
    CefRunMessageLoop();
    return 0;
}