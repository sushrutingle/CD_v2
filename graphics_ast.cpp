/**
 * AST Graphical Visualization Module
 * Uses WinBGIm library to render Abstract Syntax Tree
 */

#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "graphics_ast.h"
#include "ast.h"

// Layout configuration constants
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800
#define NODE_WIDTH 140
#define NODE_HEIGHT 40
#define LEVEL_HEIGHT 80
#define MIN_HORIZONTAL_SPACING 20
#define TOP_MARGIN 60
#define LABEL_MAX_LENGTH 20

// Color scheme for different node categories
typedef struct {
    ASTNodeType type;
    int color;
} NodeColorMap;

// Node position structure for layout calculation
typedef struct NodePosition {
    int x;
    int y;
    ASTNode* node;
    struct NodePosition* next;
} NodePosition;

// Forward declarations
static void drawTree(ASTNode* node, int x, int y, int horizontalSpace, int depth);
static void drawNode(int x, int y, const char* label, int color);
static void drawConnection(int x1, int y1, int x2, int y2);
static int getNodeColor(ASTNodeType type);
static void truncateLabel(const char* input, char* output, int maxLength);
static int calculateTreeWidth(ASTNode* node);
static int countChildren(ASTNode* node);

/**
 * Main visualization function - initializes graphics and renders the tree
 */
extern "C" void visualizeAST(ASTNode* root) {
    if (root == NULL) {
        printf("Warning: Cannot visualize NULL AST\n");
        return;
    }
    
    // Initialize graphics mode
    int gdriver = DETECT;
    int gmode;
    
    initgraph(&gdriver, &gmode, "");
    
    // Check for initialization errors
    int errorcode = graphresult();
    if (errorcode != grOk) {
        printf("Graphics error: %s\n", grapherrormsg(errorcode));
        printf("Press any key to continue...\n");
        getch();
        return;
    }
    
    // Set window title
    // Note: WinBGIm doesn't support settitle, but we can print a header
    
    // Clear screen with white background
    setbkcolor(WHITE);
    cleardevice();
    
    // Draw title banner
    setcolor(BLACK);
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    int titleWidth = textwidth("Abstract Syntax Tree Visualization");
    outtextxy((getmaxx() - titleWidth) / 2, 15, "Abstract Syntax Tree Visualization");
    
    // Draw subtitle
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    const char* subtitle = "USL Parser - Compiler Design Project";
    int subtitleWidth = textwidth(subtitle);
    outtextxy((getmaxx() - subtitleWidth) / 2, 35, subtitle);
    
    // Calculate tree width to center it properly
    int treeWidth = calculateTreeWidth(root);
    int startX = getmaxx() / 2;
    int startY = TOP_MARGIN + 10;
    
    // Draw the tree starting from root
    drawTree(root, startX, startY, treeWidth / 2, 0);
    
    // Draw legend
    setcolor(BLACK);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    int legendY = getmaxy() - 80;
    int legendX = 20;
    
    outtextxy(legendX, legendY, "Legend:");
    
    // Draw color-coded legend items
    int legendItemY = legendY + 20;
    setfillstyle(SOLID_FILL, LIGHTBLUE);
    bar(legendX, legendItemY, legendX + 15, legendItemY + 15);
    rectangle(legendX, legendItemY, legendX + 15, legendItemY + 15);
    outtextxy(legendX + 20, legendItemY + 2, "Program/Block");
    
    setfillstyle(SOLID_FILL, LIGHTGREEN);
    bar(legendX + 150, legendItemY, legendX + 165, legendItemY + 15);
    rectangle(legendX + 150, legendItemY, legendX + 165, legendItemY + 15);
    outtextxy(legendX + 170, legendItemY + 2, "Page/Property");
    
    setfillstyle(SOLID_FILL, LIGHTCYAN);
    bar(legendX + 310, legendItemY, legendX + 325, legendItemY + 15);
    rectangle(legendX + 310, legendItemY, legendX + 325, legendItemY + 15);
    outtextxy(legendX + 330, legendItemY + 2, "SEO/Meta");
    
    setfillstyle(SOLID_FILL, YELLOW);
    bar(legendX + 450, legendItemY, legendX + 465, legendItemY + 15);
    rectangle(legendX + 450, legendItemY, legendX + 465, legendItemY + 15);
    outtextxy(legendX + 470, legendItemY + 2, "Control Flow");
    
    setfillstyle(SOLID_FILL, LIGHTMAGENTA);
    bar(legendX + 590, legendItemY, legendX + 605, legendItemY + 15);
    rectangle(legendX + 590, legendItemY, legendX + 605, legendItemY + 15);
    outtextxy(legendX + 610, legendItemY + 2, "Expression/Value");
    
    // Instructions
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    setcolor(DARKGRAY);
    const char* instruction = "Press any key to close...";
    int instrWidth = textwidth(instruction);
    outtextxy((getmaxx() - instrWidth) / 2, getmaxy() - 25, instruction);
    
    // Wait for user input
    getch();
    
    // Close graphics mode
    closegraph();
}

/**
 * Recursively draws the tree with proper spacing and connections
 */
static void drawTree(ASTNode* node, int x, int y, int horizontalSpace, int depth) {
    if (node == NULL) return;
    
    // Prevent drawing beyond screen boundaries
    if (y > getmaxy() - 100) {
        return; // Tree too deep for screen
    }
    
    // Get node label
    char label[100];
    if (node->value) {
        char truncValue[LABEL_MAX_LENGTH + 1];
        truncateLabel(node->value, truncValue, LABEL_MAX_LENGTH);
        snprintf(label, sizeof(label), "%s:%s", ast_node_type_names[node->type], truncValue);
    } else {
        snprintf(label, sizeof(label), "%s", ast_node_type_names[node->type]);
    }
    
    // Truncate label if too long
    char finalLabel[LABEL_MAX_LENGTH + 1];
    truncateLabel(label, finalLabel, LABEL_MAX_LENGTH);
    
    // Draw current node
    int nodeColor = getNodeColor(node->type);
    drawNode(x, y, finalLabel, nodeColor);
    
    // Count children for spacing calculation
    int childCount = countChildren(node->child);
    
    if (childCount == 0) return;
    
    // Calculate spacing for children
    int totalWidth = childCount * NODE_WIDTH + (childCount - 1) * MIN_HORIZONTAL_SPACING;
    if (totalWidth > horizontalSpace * 2) {
        totalWidth = horizontalSpace * 2;
    }
    
    int spacing = (childCount > 1) ? totalWidth / (childCount - 1) : 0;
    int startX = x - totalWidth / 2;
    
    // Ensure minimum spacing
    if (spacing < NODE_WIDTH + MIN_HORIZONTAL_SPACING && childCount > 1) {
        spacing = NODE_WIDTH + MIN_HORIZONTAL_SPACING;
        startX = x - (spacing * (childCount - 1)) / 2;
    }
    
    // Draw children and connections
    ASTNode* child = node->child;
    int childIndex = 0;
    int nextY = y + LEVEL_HEIGHT;
    
    while (child != NULL) {
        int childX = (childCount == 1) ? x : startX + (childIndex * spacing);
        
        // Ensure child is within screen bounds
        if (childX < NODE_WIDTH / 2) childX = NODE_WIDTH / 2;
        if (childX > getmaxx() - NODE_WIDTH / 2) childX = getmaxx() - NODE_WIDTH / 2;
        
        // Draw connection line from parent to child
        drawConnection(x, y + NODE_HEIGHT / 2, childX, nextY - NODE_HEIGHT / 2);
        
        // Recursively draw child subtree
        int childHorizontalSpace = (spacing > 0) ? spacing / 2 : horizontalSpace / 2;
        drawTree(child, childX, nextY, childHorizontalSpace, depth + 1);
        
        child = child->sibling;
        childIndex++;
    }
}

/**
 * Draws a single node as a rounded rectangle with label
 */
static void drawNode(int x, int y, const char* label, int color) {
    int left = x - NODE_WIDTH / 2;
    int top = y - NODE_HEIGHT / 2;
    int right = x + NODE_WIDTH / 2;
    int bottom = y + NODE_HEIGHT / 2;
    
    // Draw rounded rectangle (approximated with arcs and lines)
    int radius = 8;
    
    // Fill node with color
    setfillstyle(SOLID_FILL, color);
    bar(left + radius, top, right - radius, bottom);
    bar(left, top + radius, left + radius, bottom - radius);
    bar(right - radius, top + radius, right, bottom - radius);
    
    // Draw rounded corners
    setcolor(BLACK);
    arc(left + radius, top + radius, 90, 180, radius);
    arc(right - radius, top + radius, 0, 90, radius);
    arc(left + radius, bottom - radius, 180, 270, radius);
    arc(right - radius, bottom - radius, 270, 360, radius);
    
    // Draw borders
    line(left + radius, top, right - radius, top);
    line(left + radius, bottom, right - radius, bottom);
    line(left, top + radius, left, bottom - radius);
    line(right, top + radius, right, bottom - radius);
    
    // Draw label text (centered)
    setcolor(BLACK);
    settextstyle(SMALL_FONT, HORIZ_DIR, 5);
    int textWidth = textwidth(label);
    int textHeight = textheight(label);
    
    // If text is too wide, use smaller font
    if (textWidth > NODE_WIDTH - 10) {
        settextstyle(SMALL_FONT, HORIZ_DIR, 4);
        textWidth = textwidth(label);
        textHeight = textheight(label);
    }
    
    int textX = x - textWidth / 2;
    int textY = y - textHeight / 2;
    
    outtextxy(textX, textY, label);
}

/**
 * Draws a connection line between parent and child nodes
 */
static void drawConnection(int x1, int y1, int x2, int y2) {
    setcolor(DARKGRAY);
    setlinestyle(SOLID_LINE, 0, 2);
    
    // Draw line with arrow
    line(x1, y1, x2, y2);
    
    // Draw arrowhead at child end
    double angle = atan2(y2 - y1, x2 - x1);
    int arrowSize = 8;
    
    int arrowX1 = x2 - arrowSize * cos(angle - 0.4);
    int arrowY1 = y2 - arrowSize * sin(angle - 0.4);
    int arrowX2 = x2 - arrowSize * cos(angle + 0.4);
    int arrowY2 = y2 - arrowSize * sin(angle + 0.4);
    
    setlinestyle(SOLID_LINE, 0, 1);
    line(x2, y2, arrowX1, arrowY1);
    line(x2, y2, arrowX2, arrowY2);
}

/**
 * Returns appropriate color based on node type category
 */
static int getNodeColor(ASTNodeType type) {
    switch (type) {
        // Program structure - Light Blue
        case AST_PROGRAM:
        case AST_STATEMENT_BLOCK:
            return LIGHTBLUE;
        
        // Page and properties - Light Green
        case AST_PAGE_DEF:
        case AST_URL_PROP:
        case AST_TITLE_PROP:
        case AST_DESC_PROP:
        case AST_TEMPLATE_PROP:
        case AST_ACCESS_PROP:
        case AST_REDIRECT_PROP:
        case AST_VARIABLE_DECL:
            return LIGHTGREEN;
        
        // SEO and Meta - Light Cyan
        case AST_SEO_BLOCK:
        case AST_META_TAGS_BLOCK:
        case AST_META_DESC:
        case AST_META_KEYWORDS:
            return LIGHTCYAN;
        
        // Control flow - Yellow
        case AST_IF_STMT:
        case AST_IF_ELSE_STMT:
        case AST_GENERATE_CONTENT:
            return YELLOW;
        
        // Navigation and content - Light Gray
        case AST_NAVIGATION:
        case AST_LINK:
        case AST_FOOTER:
        case AST_FUNCTION_CALL:
            return LIGHTGRAY;
        
        // Values and expressions - Light Magenta
        case AST_STRING_LITERAL:
        case AST_URL_PATTERN:
        case AST_VARIABLE_REF:
        case AST_IDENTIFIER:
        case AST_NUMBER:
            return LIGHTMAGENTA;
        
        default:
            return WHITE;
    }
}

/**
 * Truncates string to fit in node label
 */
static void truncateLabel(const char* input, char* output, int maxLength) {
    if (input == NULL) {
        output[0] = '\0';
        return;
    }
    
    int len = strlen(input);
    if (len <= maxLength) {
        strcpy(output, input);
    } else {
        strncpy(output, input, maxLength - 3);
        output[maxLength - 3] = '.';
        output[maxLength - 2] = '.';
        output[maxLength - 1] = '.';
        output[maxLength] = '\0';
    }
}

/**
 * Calculates the total width needed for the tree
 */
static int calculateTreeWidth(ASTNode* node) {
    if (node == NULL) return 0;
    
    int childCount = countChildren(node->child);
    if (childCount == 0) return NODE_WIDTH;
    
    int totalChildWidth = 0;
    ASTNode* child = node->child;
    while (child != NULL) {
        totalChildWidth += calculateTreeWidth(child);
        child = child->sibling;
    }
    
    int withSpacing = totalChildWidth + (childCount - 1) * MIN_HORIZONTAL_SPACING;
    return (withSpacing > NODE_WIDTH) ? withSpacing : NODE_WIDTH;
}

/**
 * Counts the number of children of a node
 */
static int countChildren(ASTNode* node) {
    int count = 0;
    while (node != NULL) {
        count++;
        node = node->sibling;
    }
    return count;
}
