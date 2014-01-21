//
//  PXSourceListDelegate.h
//  PXViewKit
//
//  Created by Alex Rozanski on 17/10/2009.
//  Copyright 2009-14 Alex Rozanski http://alexrozanski.com and other contributors.
//  This software is licensed under the New BSD License. Full details can be found in the README.
//

#import <Cocoa/Cocoa.h>

@class PXSourceList;

/**
 The `PXSourceListDelegate` protocol defines methods that can be implemented by delegates of `PXSourceList` objects.
 */
@protocol PXSourceListDelegate <NSObject>

@optional
//Extra methods
/**
 @brief Returns a Boolean value that indicates whether a particular group item is displayed as always expanded.
 @discussion A group that is displayed as *always expanded* displays no 'Show'/'Hide' button to the right on hover, and its direct children are always expanded.

 @param aSourceList The Source List that sent the message
 @param group A group item in the data source

 @return `YES` to specify that the group should be displayed as always expanded, or `NO` if not.

 @since Requires PXSourceList 2.0.0 or above.
 */
- (BOOL)sourceList:(PXSourceList*)aSourceList isGroupAlwaysExpanded:(id)group;

/**
 @brief Returns a context menu which is to be displayed for a given mouse-down event.
 @discussion See `-menuForEvent:` declared on `NSView` for more information.

 @param aSourceList The Source List that sent the message
 @param theEvent A mouse event
 @param item An item in the data source

 @return An instantiated `NSMenu` object to be displayed by the Source List for *event*, or `nil` if no menu is to be shown for the given event.

 @since Requires PXSourceList 0.8 or above.
 */
- (NSMenu*)sourceList:(PXSourceList*)aSourceList menuForEvent:(NSEvent*)theEvent item:(id)item;

//Basically NSOutlineViewDelegate wrapper methods
/**
 @brief Returns the view used to display the given item
 @discussion This method is analagous to `-outlineView:viewForTableColumn:item:` except the `NSTableColumn` parameter is omitted from this method (PXSourceList only makes use of a single table column). Aside from that, this method works in exactly the same way.
 
 Unlike when using PXSourceList in cell-based mode where the icon and badge value for each item can be set up using the PXSourceListDataSource methods, it is in this method that you should set up the icon and badge for the view (if applicable) when using PXSourceList in view-based mode. You can make use of the PXSourceListTableCellView class which exposes an outlet for a PXSourceListBadgeView (the built in view class which displays badges), and the `textField` and `imageView` outlets (which are inherited from its superclass, `NSTableCellView`) for the item's label and icon, respectively.

 @param aSourceList The Source List that sent the message
 @param item An item in the data source

 @return The view to display for the specified item, or `nil` if you don't want to display a view for the item.
 
 @warning This is a required method when using the Source List in view-based mode.

 @since Requires PXSourceList 2.0.0 or above.
 */
- (NSView *)sourceList:(PXSourceList *)aSourceList viewForItem:(id)item;

/**
 @brief Returns the view used to display the given row.
 @discussion See `-outlineView:rowViewForItem:` declared on `NSOutlineViewDelegate` for more information.

 @param aSourceList The Source List that sent the message
 @param item An item in the data source

 @return An `NSTableRowView` instance. As with `NSOutlineViewDelegate`, if `nil` is returned for a row, an `NSTableRowView` instance will be created by the Source List and used instead.

 @since Requires PXSourceList 2.0.0 or above.
 */
- (NSTableRowView *)sourceList:(PXSourceList *)aSourceList rowViewForItem:(id)item;

/**
 @brief Sent when a row view has been added to the Source List.
 @discussion See `-outlineView:didAddRowView:forRow:` declared on `NSOutlineViewDelegate` for more information.

 @param aSourceList The Source List that sent the message
 @param rowView The view that was added to the Source List
 @param row The row index

 @since Requires PXSourceList 2.0.0 or above.
 */
- (void)sourceList:(PXSourceList *)aSourceList didAddRowView:(NSTableRowView *)rowView forRow:(NSInteger)row;

/**
 @brief Sent when a row view has been removed to the Source List.
 @discussion See `-outlineView:didRemoveRowView:forRow:` declared on `NSOutlineViewDelegate` for more information.

 @param aSourceList The Source List that sent the message
 @param rowView The view that was removed
 @param row The row index

 @since Requires PXSourceList 2.0.0 or above.
 */
- (void)sourceList:(PXSourceList *)aSourceList didRemoveRowView:(NSTableRowView *)rowView forRow:(NSInteger)row;

- (BOOL)sourceList:(PXSourceList*)aSourceList shouldSelectItem:(id)item;
- (NSIndexSet*)sourceList:(PXSourceList*)aSourceList selectionIndexesForProposedSelection:(NSIndexSet *)proposedSelectionIndexes;

- (NSString *)sourceList:(PXSourceList *)sourceList toolTipForCell:(NSCell *)cell rect:(NSRectPointer)rect item:(id)item mouseLocation:(NSPoint)mouseLocation;

- (NSString *)sourceList:(PXSourceList *)sourceList typeSelectStringForItem:(id)item;
- (id)sourceList:(PXSourceList *)sourceList nextTypeSelectMatchFromItem:(id)startItem toItem:(id)endItem forString:(NSString *)searchString;
- (BOOL)sourceList:(PXSourceList *)sourceList shouldTypeSelectForEvent:(NSEvent *)event withCurrentSearchString:(NSString *)searchString;
- (BOOL)sourceList:(PXSourceList *)sourceList shouldShowCellExpansionForItem:(id)item;

- (BOOL)sourceList:(PXSourceList*)aSourceList shouldEditItem:(id)item;

- (BOOL)sourceList:(PXSourceList*)aSourceList shouldTrackCell:(NSCell *)cell forItem:(id)item;

- (BOOL)sourceList:(PXSourceList*)aSourceList shouldExpandItem:(id)item;
- (BOOL)sourceList:(PXSourceList*)aSourceList shouldCollapseItem:(id)item;

- (CGFloat)sourceList:(PXSourceList*)aSourceList heightOfRowByItem:(id)item;

- (NSCell*)sourceList:(PXSourceList*)aSourceList willDisplayCell:(id)cell forItem:(id)item;
- (NSCell*)sourceList:(PXSourceList*)aSourceList dataCellForItem:(id)item;

@end

@interface NSObject (PXSourceListNotifications)

//Selection
- (void)sourceListSelectionIsChanging:(NSNotification *)notification;
- (void)sourceListSelectionDidChange:(NSNotification *)notification;

//Item expanding/collapsing
- (void)sourceListItemWillExpand:(NSNotification *)notification;
- (void)sourceListItemDidExpand:(NSNotification *)notification;
- (void)sourceListItemWillCollapse:(NSNotification *)notification;
- (void)sourceListItemDidCollapse:(NSNotification *)notification;

- (void)sourceListDeleteKeyPressedOnRows:(NSNotification *)notification;


@end

//PXSourceList delegate notifications
extern NSString * const PXSLSelectionIsChangingNotification;
extern NSString * const PXSLSelectionDidChangeNotification;
extern NSString * const PXSLItemWillExpandNotification;
extern NSString * const PXSLItemDidExpandNotification;
extern NSString * const PXSLItemWillCollapseNotification;
extern NSString * const PXSLItemDidCollapseNotification;
extern NSString * const PXSLDeleteKeyPressedOnRowsNotification;

