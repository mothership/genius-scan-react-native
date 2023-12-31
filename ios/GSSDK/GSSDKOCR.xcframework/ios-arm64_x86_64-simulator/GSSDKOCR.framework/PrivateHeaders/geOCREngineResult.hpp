// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from sdk-ocr.djinni

#pragma once

#include "geOCREngineError.hpp"
#include "geTextLayout.hpp"
#include <optional>
#include <string>
#include <utility>

namespace ge {

/** The result of the OCR */
struct OCREngineResult final {
    OCREngineError status;
    std::optional<std::string> text;
    std::optional<::ge::TextLayout> textLayout;

    OCREngineResult(OCREngineError status_,
                    std::optional<std::string> text_,
                    std::optional<::ge::TextLayout> text_layout_)
    : status(std::move(status_))
    , text(std::move(text_))
    , textLayout(std::move(text_layout_))
    {}

    OCREngineResult()
    : status()
    , text()
    , textLayout()
    {}
};

}  // namespace ge
