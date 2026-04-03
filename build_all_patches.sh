#!/usr/bin/env bash

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

FEATURE_FLAGS=(SFX PLUS PLAYTEST PARADISE)
TARGET="rhythmheavenadvance"
PATCH_DIR="patches"
TOTAL_COMBINATIONS=$((1 << ${#FEATURE_FLAGS[@]}))

if ! command -v flips >/dev/null 2>&1; then
    echo "Error: 'flips' is required but was not found in PATH." >&2
    exit 1
fi

if command -v nproc >/dev/null 2>&1; then
    DEFAULT_JOBS="$(nproc)"
else
    DEFAULT_JOBS=4
fi
JOBS="${JOBS:-$DEFAULT_JOBS}"
MAKE_OUTPUT_MODE="${MAKE_OUTPUT_MODE:-quiet}"

mkdir -p "$PATCH_DIR"
rm -f "$PATCH_DIR"/"${TARGET}"_*.bps

feature_slug() {
    if [[ $# -eq 0 ]]; then
        echo "vanilla"
        return
    fi

    local slug=""
    local feature
    for feature in "$@"; do
        local lower="${feature,,}"
        if [[ -z "$slug" ]]; then
            slug="$lower"
        else
            slug="${slug}_$lower"
        fi
    done
    echo "$slug"
}

for ((mask = 0; mask < TOTAL_COMBINATIONS; mask++)); do
    enabled_features=()

    for ((idx = 0; idx < ${#FEATURE_FLAGS[@]}; idx++)); do
        if ((mask & (1 << idx))); then
            enabled_features+=("${FEATURE_FLAGS[$idx]}")
        fi
    done

    features_value="${enabled_features[*]}"
    slug="$(feature_slug "${enabled_features[@]}")"
    output_patch="$PATCH_DIR/${TARGET}_${slug}.bps"

    if [[ ${#enabled_features[@]} -eq 0 ]]; then
        feature_label="<none>"
    else
        feature_label="$features_value"
    fi

    printf '[%02d/%02d] Building FEATURES="%s"\n' "$((mask + 1))" "$TOTAL_COMBINATIONS" "$feature_label"

    make_common_args=(--no-print-directory "MAKE_OUTPUT=$MAKE_OUTPUT_MODE")

    make "${make_common_args[@]}" distclean
    make_args=("${make_common_args[@]}" -j"$JOBS")
    if [[ ${#enabled_features[@]} -ne 0 ]]; then
        make_args+=("FEATURES=$features_value")
    fi
    make "${make_args[@]}" patch

    cp -f "build/${TARGET}.bps" "$output_patch"
    printf 'Saved %s\n' "$output_patch"
done

echo "Done. Generated ${TOTAL_COMBINATIONS} patch files in ${PATCH_DIR}/"